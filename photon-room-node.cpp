#include "application.h"
#include "general.h"

#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "Adafruit_BME280\Adafruit_Sensor.h"

#include "Views\icons\humidity64.h"
#include "Views\icons\humidity32.h"
#include "Views\icons\temperature64.h"
#include "Views\icons\temperature32.h"
#include "Views\icons\pressure64.h"
#include "Views\icons\pressure32.h"
#include "Views\icons\gas64.h"
#include "Views\icons\gas32.h"

#include "Sensors\Bme280DataCollector.h"
#include "Sensors\AnalogDataCollector.h"
#include "Views\AllSensorDataComponent.h"
#include "Views\AllSensorDataComponent2.h"
#include "Views\HeaderComponent.h"
#include "Views\FooterComponent.h"
#include "Views\Component.h"
#include "Views\Container.h"
#include "Views\SplashComponent.h"
#include "Views\AlarmComponent.h"
#include "DataCollection.h"
#include "Alarm.h"
#include "MeasureDefinitions.h"
#include "queue.h"
#include "DataPublisher.h"

#define INFLUXDB_DB	 "measures"

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
MeasureMeta** measures = (MeasureMeta**)malloc(3 * sizeof(MeasureMeta*));
QueueList<Action> actionsQueue;

/*
Timers
*/
void onCollectionTimerElapsed();
Timer collectionTimer(10000, onCollectionTimerElapsed);

void onOperationalMetricsTimerElapsed();
Timer operationalMetricsCollectionTimer(30000, onOperationalMetricsTimerElapsed);

void onAutoRotateViewTimerElapsed();
bool isAutoRotateViewOn = false;
Timer autoRotateViewTimer(10000, onAutoRotateViewTimerElapsed);

/*
Views declarations
*/
Container container;
HeaderComponent headerComponent;
FooterComponent footerComponent;
SplashComponent splashComponent;

/*
Measures declarations
*/
TemperatureDataCollector tempDataCollector(&bme);
BoundariesMeasureCheck temperatureWarningBoundaries = BoundariesMeasureCheck(27.0, 32.0);
BoundariesMeasureCheck temperatureCriticalBoundaries = BoundariesMeasureCheck(32.0, 999.0);
MeasureMeta temperatureMeasure = MeasureMeta(
	1,
	&temperatureWarningBoundaries, // warning
	&temperatureCriticalBoundaries, // error
	&tempDataCollector,
	"%2.1fC");

HumidityDataCollector humidityDataCollector(&bme);
MeasureMeta humidityMeasure = MeasureMeta(2, &humidityDataCollector, "%2.1f");

PressureDataCollector pressureDataCollector(&bme);
MeasureMeta pressureMeasure = MeasureMeta(3, &pressureDataCollector, "%4.0f");

AnalogDataCollector mq2DataCollector(A0);
BoundariesMeasureCheck mq2WarningBoundaries = BoundariesMeasureCheck(10000.0, 20000.0);
BoundariesMeasureCheck mq2CriticalBoundaries = BoundariesMeasureCheck(20000.0, 999999.0);
MeasureMeta mq2Measure = MeasureMeta(
	4, 
	&mq2WarningBoundaries,
	&mq2CriticalBoundaries,
	&mq2DataCollector, 
	"%4.1f");

AllSensorDataComponent summaryView(measures);
AllSensorDataComponent2 temperatureView(&temperatureMeasure);
AllSensorDataComponent2 humidityView(&humidityMeasure);
AllSensorDataComponent2 pressureView(&pressureMeasure);
AllSensorDataComponent2 mq2View(&mq2Measure);
AlarmComponent alarmComponent(measures);
Alarm alarm(D4, &alarmComponent);

/*
Few issues worth mentioning:
- do nothing in constructors, only in begin() as crashed the photon couple of time (red light)
- pass global objects using obj address, not full object as doing a shadow copy and this mess up object local values
- REMINDER: NO DELAY IN ISR
*/
IPAddress zookeeperIP(157, 20, 16, 106);
UDP udpClient;
InfluxDBDataPublisher dataPublisher(zookeeperIP, &udpClient, 8089,  "measures");

void onButton1Pressed()
{
	digitalWrite(D4, HIGH);
	//if (isAutoRotateViewOn)
	//{
	//	// if the user presses button1 while in auto rotate mode, the rotation is cancelled
	//	autoRotateViewTimer.stop();
	//	isAutoRotateViewOn = false;
	//}
	//else
	//{
	//	autoRotateViewTimer.start();
	//	isAutoRotateViewOn = true;
	//}
	
	if (actionsQueue.peek() != Event_Button1Pressed)
		actionsQueue.push(Event_Button1Pressed);

	digitalWrite(D4, LOW);
}

void onButton2Pressed()
{
	digitalWrite(D4, HIGH);
	if (actionsQueue.peek() != Event_Button2Pressed)
		actionsQueue.push(Event_Button2Pressed);
	digitalWrite(D4, LOW);
}

void startAlarm()
{
	alarm.TriggerAlarm(&container);
	actionsQueue.push(Event_AlarmTriggered);
}

void stopAlarm()
{
	alarm.DisableAlarm(&container);
	actionsQueue.push(Event_AlarmStopped);
}

void onMeasureCollectionDone(MeasureMeta * measure)
{
	dataPublisher.publish(measure->metricName, measure->latestValue);

	if (alarm.CheckForAlerts() != MeasureZone_Normal && !alarm.IsTriggered())
	{
		actionsQueue.clear();
		actionsQueue.push(Event_StartAlarmRequested);
	}
}

void onCollectionTimerElapsed()
{
	// collect
	actionsQueue.push(Event_MeasureCollectionStarted);
	dataCollectorManager.Collect(onMeasureCollectionDone);
	actionsQueue.push(Event_MeasureCollectionCompleted);

	//
	// stop the alarm if any of the sensors triggered it
	if (alarm.CheckForAlerts() == MeasureZone_Normal && alarm.IsTriggered())
	{
		actionsQueue.clear();
		actionsQueue.push(Event_StopAlarmRequested);
	}
}

void onOperationalMetricsTimerElapsed()
{
	bool isReady = WiFi.ready();
	int signalQuality = WiFi.RSSI(); // returns a value between -127 and -1
	float signalInPercent = (signalQuality + 127.0) / (127.0 - 1.0);

	dataPublisher.publish("wifi-strength", signalInPercent);
	dataPublisher.publish("wifi-status", isReady ? 1 : 0);
	dataPublisher.publish("device-freememory", System.freeMemory());
	
	int alarmLevel = alarm.CheckForAlerts();
	dataPublisher.publish("alarm-status", alarmLevel == MeasureZone_Critical ? 2 : (alarmLevel == MeasureZone_Warning ? 1 : 0 ));
}

void onAutoRotateViewTimerElapsed()
{
	if (actionsQueue.peek() != Action_SwitchToNextView)
		actionsQueue.push(Action_SwitchToNextView);
}

/*
PHOTON SETUP
*/
void setup()
{
	// todo: need to use a hash table rather than this trick as need to have id such as "TMP"
	measures[TEMPERATURE_MEASURE_ID] = &temperatureMeasure;
	measures[HUMIDITY_MEASURE_ID] = &humidityMeasure;
	measures[PRESSURE_MEASURE_ID] = &pressureMeasure;
	measures[MQ2_MEASURE_ID] = &mq2Measure;

	temperatureMeasure.name = "Temperature";
	temperatureMeasure.shortName = "TEMP";
	temperatureMeasure.metricName = "temperature";
	temperatureMeasure.progressBarMin = 5;
	temperatureMeasure.progressBarMax = 35;
	temperatureMeasure.icon64 = new Icon(&temperature64[0], temperature64_offsetTopX, temperature64_offsetTopY, temperature64_offsetBottomX, temperature64_offsetBottomY);
	temperatureMeasure.icon32 = new Icon(&temperature32[0], temperature32_offsetTopX, temperature32_offsetTopY, temperature32_offsetBottomX, temperature32_offsetBottomY);

	humidityMeasure.name = "Humidity";
	humidityMeasure.shortName = "HUM";
	humidityMeasure.metricName = "humidity";
	humidityMeasure.progressBarMin = 0;
	humidityMeasure.progressBarMax = 100;
	humidityMeasure.icon64 = new Icon(&humidity64[0], humidity64_offsetTopX, humidity64_offsetTopY, humidity64_offsetBottomX, humidity64_offsetBottomY);
	humidityMeasure.icon32 = new Icon(&humidity32[0], humidity32_offsetTopX, humidity32_offsetTopY, humidity32_offsetBottomX, humidity32_offsetBottomY);

	pressureMeasure.name = "Pressure";
	pressureMeasure.shortName = "PRESS";
	pressureMeasure.metricName = "pressure";
	pressureMeasure.progressBarMin = 950;
	pressureMeasure.progressBarMax = 1200;
	pressureMeasure.icon64 = new Icon(&pressure64[0], pressure64_offsetTopX, pressure64_offsetTopY, pressure64_offsetBottomX, pressure64_offsetBottomY);
	pressureMeasure.icon32 = new Icon(&pressure32[0], pressure32_offsetTopX, pressure32_offsetTopY, pressure32_offsetBottomX, pressure32_offsetBottomY);

	mq2Measure.name = "MQ-2";
	mq2Measure.shortName = "CO GAS";
	mq2Measure.metricName = "MQ-2";
	mq2Measure.progressBarMin = 0;
	mq2Measure.progressBarMax = 9999;
	mq2Measure.icon64 = new Icon(&gas64[0], gas64_offsetTopX, gas64_offsetTopY, gas64_offsetBottomX, gas64_offsetBottomY);
	mq2Measure.icon32 = new Icon(&gas32[0], gas32_offsetTopX, gas32_offsetTopY, gas32_offsetBottomX, gas32_offsetBottomY);

	dataPublisher.init();

	//
	// Displpay init
	display.begin();
	display.fillScreen(ILI9341_BLACK);
	display.setRotation(1);

	//
	// Views init
	container.setHeader(&headerComponent);
	container.setFooter(&footerComponent);
	container.addView(&splashComponent);
	container.addView(&summaryView);
	container.addView(&temperatureView);
	container.addView(&humidityView);
	container.addView(&pressureView);
	container.addView(&mq2View);
	container.init(&display);

	//
	// Interruptions setup
	pinMode(BoardInput_Button1, INPUT_PULLUP);
	pinMode(BoardInput_Button2, INPUT_PULLUP);
	attachInterrupt(BoardInput_Button1, onButton1Pressed, FALLING);
	attachInterrupt(BoardInput_Button2, onButton2Pressed, FALLING);

	alarm.Init(measures);
	
	dataCollectorManager.Init(measures);
	Particle.publish("events.photon.setup", "done");
	actionsQueue.push(Action_SwitchToNextView);
	collectionTimer.start();
	operationalMetricsCollectionTimer.start();
	//autoRotateViewTimer.start(); 
	isAutoRotateViewOn = true;
}

/*
PHOTON LOOP
*/
void loop()
{
	delay(100);
	if (actionsQueue.isEmpty())
		return;

	Action actionToDo = actionsQueue.pop();

	while (actionToDo != Action_None)
		switch (actionToDo)
		{
			case Action_None: break;
			case Event_StartAlarmRequested: startAlarm(); actionToDo = Action_None;  break;
			case Event_StopAlarmRequested: stopAlarm(); actionToDo = Action_None; break;
			case Event_MeasureCollectionCompleted: container.refresh(); actionToDo = Action_None; break;
			default: 
				actionToDo = container.handleEvent(actionToDo);
				break;
		}
}


