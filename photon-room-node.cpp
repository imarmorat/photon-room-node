#include "application.h"
#include "general.h"

#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "Adafruit_BME280\Adafruit_Sensor.h"

#include "Sensors\Bme280DataCollector.h"
#include "Sensors\AnalogDataCollector.h"
#include "Views\AllSensorDataComponent.h"
#include "Views\AllSensorDataComponent2.h"
#include "Views\StatComponent.h"
#include "Views\HeaderComponent.h"
#include "Views\FooterComponent.h"
#include "Views\Component.h"
#include "Views\Container.h"
#include "Views\SplashComponent.h"
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
Adafruit_BME280 bme;
DataCollectorManager dataCollectorManager(D7);
Alarm alarm(D4, &display);
MeasureMeta** measures = (MeasureMeta**)malloc(3 * sizeof(MeasureMeta*));

Action actionToDo;

/*
Views declarations
*/
Container container;
HeaderComponent headerComponent;
FooterComponent footerComponent;
SplashComponent splashComponent;
StatComponent statsComponent;
AllSensorDataComponent overallSensorDataComponent(measures);
AllSensorDataComponent2 overallSensorDataComponent2(measures);

TemperatureDataCollector tempDataCollector(&bme);
BoundariesMeasureCheck temperatureWarningBoundaries = BoundariesMeasureCheck(10.0, 26.0);
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

void onButton1Pressed()
{
	digitalWrite(D4, HIGH);
	actionToDo = Event_Button1Pressed;
	digitalWrite(D4, LOW);
}

void onButton2Pressed()
{
	digitalWrite(D4, HIGH);
	actionToDo = Event_Button2Pressed;
	digitalWrite(D4, LOW);
}

void stopAlarm()
{
	noInterrupts();
	alarm.DisableAlarm();
	interrupts();

	actionToDo = Event_AlarmStopped;
}

void onMeasureCollectionDone(MeasureMeta * measure)
{
	noInterrupts();

	alarm.CheckForAlerts();
	if (!alarm.IsTriggered())
		actionToDo = Event_MeasureCollectionCompleted;

	interrupts();
}

void onTimerElapsed()
{
	// collect
	actionToDo = Event_MeasureCollectionStarted;
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
	display.setRotation(3);

	//
	// Views init
	container.setHeader(&headerComponent);
	container.setFooter(&footerComponent);
	container.addView(&splashComponent);
	container.addView(&overallSensorDataComponent2);
	container.init(&display);

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
	//Particle.publish("action", String::format("%d", actionToDo));
	switch (actionToDo)
	{
		case Action_None: break;
		case Event_StopAlarmRequested:
			stopAlarm(); 
			break;
		default: 
			// anything that is not handled by the loop code is propagated to the container
			actionToDo = container.handleEvent(actionToDo);
			break;
	}
}


