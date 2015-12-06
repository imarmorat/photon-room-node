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

#define OLED_RESET D4

/*
    BME definitions
*/
#define BME_SCK D4
#define BME_MISO D3
#define BME_MOSI D2
#define BME_CS D5
#define SEALEVELPRESSURE_HPA (1013.25)


/*
    General declarations
*/
Adafruit_SSD1306 display(OLED_RESET);
DataCollectorManager dataCollectorManager(D7);
Alarm alarm(D2, &display);

/*
    Views declarations
*/
SplashView splashView;
StatView statsView;
AllSensorDataView overallSensorDataView;

#define VIEW_COUNT 3
View* views[VIEW_COUNT];
volatile int currentViewIndex;

Action actionToDo;

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
	actionToDo = views[currentViewIndex]->handleInput(BoardInput_Button1);
}

void onButton2Pressed()
{
	actionToDo = views[currentViewIndex]->handleInput(BoardInput_Button2);
}

void stopAlarm()
{
	noInterrupts();
	
	alarm.DisableAlarm();

	// reattach normal behaviour to user inputs
	attachInterrupt(BoardInput_Button1, onButton1Pressed, FALLING);
	attachInterrupt(BoardInput_Button2, onButton2Pressed, FALLING);

	interrupts();

	// come back to the current view
	views[currentViewIndex]->display(&display);
}

void onMeasureCollectionDone(MeasureMeta * measure)
{
	noInterrupts();

	alarm.CheckForAlerts();

	attachInterrupt(BoardInput_Button1, stopAlarm, FALLING);
	attachInterrupt(BoardInput_Button2, stopAlarm, FALLING);
	
	interrupts();
}

void onTimerElapsed()
{
	// collect
	dataCollectorManager.Collect(onMeasureCollectionDone);
}

/*
	PHOTON SETUP
*/
void setup() 
{
	measures[0] = &temperatureMeasure;
	measures[1] = &humidityMeasure;
	measures[2] = &pressureMeasure;
	measures[3] = &mq2Measure;

	dataCollectorManager.Init(measures);
	alarm.Init(measures);

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
	pinMode(BoardInput_Button2, INPUT_PULLUP);
	attachInterrupt(BoardInput_Button1, onButton1Pressed, FALLING);
	attachInterrupt(BoardInput_Button2, onButton2Pressed, FALLING);
    
    actionToDo = Action_SwitchToNextView;
	Timer t = Timer(500, &onTimerElapsed);
}

/*
	PHOTON LOOP
*/
void loop() 
{
    delay(100);
    switch(actionToDo)
    {
        case Action_None: break;
        case Action_SwitchToNextView: switchView(); break;
		case Action_StopAlarm: stopAlarm(); break;
		//case CollectData: dataCollectorManager.Collect(); break;
    }
    
    actionToDo = Action_None;
}


