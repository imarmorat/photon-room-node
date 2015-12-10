#include "application.h"
#include "general.h"

#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
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

/*
BME definitions
*/
#define BME_SCK D6
#define BME_MISO D6
#define BME_MOSI D6
#define BME_CS D6
#define SEALEVELPRESSURE_HPA (1013.25)


/*
General declarations
*/
Adafruit_ILI9341 display = Adafruit_ILI9341(A2, D6, A1);
DataCollectorManager dataCollectorManager(D7);
Alarm alarm(D4, &display);
MeasureMeta** measures = (MeasureMeta**)malloc(3 * sizeof(MeasureMeta*));

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
BoundariesMeasureCheck temperatureWarningBoundaries = BoundariesMeasureCheck(10.0, 25.0);
BoundariesMeasureCheck temperatureCriticalBoundaries = BoundariesMeasureCheck(0.0, 40.0);
MeasureMeta temperatureMeasure = MeasureMeta(
	1,
	&temperatureWarningBoundaries, // warning
	&temperatureCriticalBoundaries, // error
	&tempDataCollector);

HumidityDataCollector humidityDataCollector(&bme);
MeasureMeta humidityMeasure = MeasureMeta(2, &humidityDataCollector);

PressureDataCollector pressureDataCollector(&bme);
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
- REMINDER: NO DELAY IN ISR
*/


void switchView()
{
	noInterrupts();

	currentViewIndex++;
	if (currentViewIndex >= VIEW_COUNT)
		currentViewIndex = 0;

	display.setRotation(1);
	views[currentViewIndex]->display(&display);

	interrupts();
}

void refreshView()
{
	display.setRotation(1);
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

	refreshView();
}

void onMeasureCollectionDone(MeasureMeta * measure)
{
	noInterrupts();

	alarm.CheckForAlerts();
	if (!alarm.IsTriggered())
		actionToDo = Action_RefreshView;

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
	// todo: need to use a hash table rather than this trick as need to have id such as "TMP"
	measures[TEMPERATURE_MEASURE_ID] = &temperatureMeasure;
	measures[HUMIDITY_MEASURE_ID] = &humidityMeasure;
	measures[PRESSURE_MEASURE_ID] = &pressureMeasure;
	//measures[3] = &mq2Measure;

	//
	// Displpay init
	display.begin();
	display.fillScreen(ILI9341_BLACK);
	display.setRotation(1);

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

	alarm.Init(measures);

	actionToDo = Action_SwitchToNextView;
	dataCollectorManager.Init(measures);
	Particle.publish("events.photon.setup", "done");
	t.start();
}

/*
PHOTON LOOP
*/
void loop()
{
	delay(100);
	switch (actionToDo)
	{
	case Action_None: break;
	case Action_SwitchToNextView: switchView(); break;
	case Action_StopAlarm: stopAlarm(); break;
	case Action_RefreshView: refreshView(); break;
	}

	actionToDo = Action_None;
}


