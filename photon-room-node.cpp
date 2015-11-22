#include "application.h"

#include "Adafruit_SSD1306\Adafruit_SSD1306.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "Adafruit_BME280\Adafruit_Sensor.h"

#include "SensorDataManager.h"
#include "AllSensorDataView.h"
#include "StatView.h"
#include "View.h"
#include "SplashView.h"
#include "DataCollection.h"
#include "AnalogDataCollector.h"

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
Adafruit_BME280 bme;
SensorDataManager sensorData(bme);
DataCollectorManager dataCollectorManager(D7);

void noActionAlarmCallback(float value) {}

AnalogDataCollector mq2GasSensor(D3, 100, 11000, 100, &noActionAlarmCallback, 1000, &noActionAlarmCallback);

/*
    Views declarations
*/
SplashView splashView;
StatView statsView;
AllSensorDataView overallSensorDataView;

#define VIEW_COUNT 3
View* views[VIEW_COUNT];
volatile int currentViewIndex;

/*
    Input/output declarations
*/
#define BUTTONS_CHANGE_VIEW D3

enum Action { 
	None = 0,
	SwitchToNextView = 1,
	//CollectData =2
};

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

void onChangeViewRequest()
{
    actionToDo = SwitchToNextView;
}

void setup() 
{
	//
	// Data collection
	dataCollectorManager.AddCollector(&sensorData);
	dataCollectorManager.AddCollector(&mq2GasSensor);
	dataCollectorManager.Init();

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

    views[currentViewIndex]->display(&display);
    delay(5000);
    
    overallSensorDataView.begin(&display, &sensorData);
    delay(2000);
    
    //
    // Interruptions setup
    pinMode(BUTTONS_CHANGE_VIEW, INPUT_PULLUP);
    attachInterrupt(BUTTONS_CHANGE_VIEW, onChangeViewRequest, FALLING);
    
    actionToDo = None;
}

void loop() 
{
    delay(100);
    switch(actionToDo)
    {
        case None: break;
        case SwitchToNextView: switchView(); break;
		//case CollectData: dataCollectorManager.Collect(); break;
    }
    
    actionToDo = None;
}



