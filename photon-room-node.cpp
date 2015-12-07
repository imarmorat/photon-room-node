#include "application.h"
#include "general.h"

#include "Adafruit_SSD1306\Adafruit_SSD1306.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "Adafruit_BME280\Adafruit_Sensor.h"

#include "Sensors\Bme280DataCollector.h"
#include "Sensors\AnalogDataCollector.h"
#include "Views\AllSensorDataView.h"
#include "Views\StatView.h"
#include "Views\View.h"
#include "Views\SplashView.h"
#include "DataCollection.h"
#include "Alarm.h"
#include "MeasureDefinitions.h"

#define OLED_RESET D6

/*
    BME definitions
*/
#define BME_SCK D6
#define BME_MISO D6
#define BME_MOSI D6
#define BME_CS D6
#define SEALEVELPRESSURE_HPA (1013.25)

/* REMINDER: NO DELAY IN ISR */

MeasureMeta** measures = (MeasureMeta**)malloc(3*sizeof(MeasureMeta*));

/*
    General declarations
*/
Adafruit_SSD1306 display(OLED_RESET);
DataCollectorManager dataCollectorManager(D7);
Alarm alarm(D4, &display);

/*
    Views declarations
*/
SplashView splashView;
StatView statsView;
AllSensorDataView overallSensorDataView(measures);

#define VIEW_COUNT 3
View* views[VIEW_COUNT];
volatile int currentViewIndex;

Action actionToDo;

Adafruit_BME280 bme;
TemperatureDataCollector tempDataCollector(&bme);
HumidityDataCollector humidityDataCollector(&bme);
PressureDataCollector pressureDataCollector(&bme);

MeasureMeta temperatureMeasure = MeasureMeta(
		1,
		BoundariesMeasureCheck(10.0, 23.0), // warning
		BoundariesMeasureCheck(0.0, 40.0), // error
		&tempDataCollector);
MeasureMeta humidityMeasure = MeasureMeta(2, &humidityDataCollector);
MeasureMeta pressureMeasure = MeasureMeta(3, &pressureDataCollector);
	
//AnalogDataCollector mq2GasSensor(D3);
//MeasureMeta mq2Measure = MeasureMeta(
//	4,
//	BoundariesMeasureCheck(0, 100),
//	BoundariesMeasureCheck(0, 1000),
//	&mq2GasSensor);
	
/* 
    Few issues worth mentioning:
    - do nothing in constructors, only in begin() as crashed the photon couple of time (red light)
    - pass global objects using obj address, not full object as doing a shadow copy and this mess up object local values
*/
void switchView()
{
    currentViewIndex++;
    if (currentViewIndex >= VIEW_COUNT)
        currentViewIndex = 0;
    
    views[currentViewIndex]->display(&display);
}

void onButton1Pressed()
{
	digitalWrite(D4, HIGH);
	actionToDo = views[currentViewIndex]->handleInput(BoardInput_Button1);
	digitalWrite(D4, LOW);
}

void onButton2Pressed()
{
	actionToDo = views[currentViewIndex]->handleInput(BoardInput_Button2);
}

void stopAlarm()
{
	noInterrupts();
	
	alarm.DisableAlarm();

	interrupts();

	// come back to the current view
	views[currentViewIndex]->display(&display);
}

void onMeasureCollectionDone(MeasureMeta * measure)
{
	noInterrupts();

	alarm.CheckForAlerts();
	
	interrupts();
}

void onTimerElapsed()
{
	// collect
	dataCollectorManager.Collect(onMeasureCollectionDone);
}

Timer t(5000, onTimerElapsed);

/*
	PHOTON SETUP
*/
void setup() 
{	
	measures[TEMPERATURE_MEASURE_ID] = &temperatureMeasure;
	measures[HUMIDITY_MEASURE_ID] = &humidityMeasure;
	measures[PRESSURE_MEASURE_ID] = &pressureMeasure;
	//measures[3] = &mq2Measure;

    //
    // Displpay init
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	delay(2000);
    display.clearDisplay();

    //
    // Views init
    views[0] = &splashView;
	views[1] = &overallSensorDataView;
    views[2] = &statsView;
    currentViewIndex = 0;

	//
	// Shows splash view
    views[currentViewIndex]->display(&display);
    delay(5000);
    
    //
    // Interruptions setup
	pinMode(BoardInput_Button1, INPUT_PULLUP);
	//pinMode(BoardInput_Button2, INPUT_PULLUP);
	attachInterrupt(BoardInput_Button1, onButton1Pressed, FALLING);
	//attachInterrupt(BoardInput_Button2, onButton2Pressed, FALLING);
    
	dataCollectorManager.Init(measures);
	alarm.Init(measures);
	
    actionToDo = Action_SwitchToNextView;
	t.start();
	Particle.publish("event", "setup completed");
	dataCollectorManager.Collect(onMeasureCollectionDone);
	Particle.publish("event", "first data completion complete");
}

/*
	PHOTON LOOP
*/
void loop() 
{
    delay(100);
    switch(actionToDo)
    {
        case Action_None: views[currentViewIndex]->display(&display);break;
        case Action_SwitchToNextView: switchView(); break;
		case Action_StopAlarm: stopAlarm(); break;
    }
    
    actionToDo = Action_None;
}


