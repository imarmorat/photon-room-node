#include "application.h"

#include "Adafruit_SSD1306\Adafruit_SSD1306.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "Adafruit_BME280\Adafruit_Sensor.h"

#include "Sensors\Bme280DataCollector.h"
#include "Sensors\AnalogDataCollector.h"
//#include "Views\AllSensorDataView.h"
#include "Views\StatView.h"
#include "Views\View.h"
#include "Views\SplashView.h"
#include "DataCollection.h"

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
TemperatureDataCollector tempDataCollector(&bme);
HumidityDataCollector humidityDataCollector(&bme);
PressureDataCollector pressureDataCollector(&bme);
DataCollectorManager dataCollectorManager(D7);
AnalogDataCollector mq2GasSensor(D3);



/*
    Views declarations
*/
SplashView splashView;
StatView statsView;
//AllSensorDataView overallSensorDataView;

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
	MeasureMeta tempMeasure = { 1, true , 10.0, 30.0, 0.0, 40.0, -1, &tempDataCollector };
	MeasureMeta humidityMeasure = { 2, false, -9999, -9999, -9999, -9999, -1, &humidityDataCollector };
	MeasureMeta pressureMeasure = { 3, false,  -9999, -9999, -9999, -9999, -1, &tempDataCollector };
	MeasureMeta m2Measure = { 4, true, 0, 100, 0, 1000, -1, &mq2GasSensor };

	//
	// Data collection
	dataCollectorManager.AddCollector(&tempMeasure);
	dataCollectorManager.AddCollector(&humidityMeasure);
	dataCollectorManager.AddCollector(&pressureMeasure);
	dataCollectorManager.AddCollector(&m2Measure);
	dataCollectorManager.Init();

    //
    // Displpay init
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	delay(2000);
    display.clearDisplay();

    //
    // Views init
    views[0] = &splashView;
//    views[1] = &overallSensorDataView;
    views[2] = &statsView;
    currentViewIndex = 0;

    views[currentViewIndex]->display(&display);
    delay(5000);
    
 //   overallSensorDataView.begin(&display, &sensorData);
 //   delay(2000);
    
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



