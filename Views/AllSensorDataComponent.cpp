#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "../DataCollection.h"
#include "AllSensorDataComponent.h"
#include "Component.h"

// todo: I dont like having external static used here, need to get them passed through at some point
// e.g. by passing Measures + some id

AllSensorDataComponent::AllSensorDataComponent(MeasureMeta** measures) : _measures(measures)
{
    /* remember to be extra careful here, had some crashes on photon when doing some init things here */
}

void AllSensorDataComponent::begin(Adafruit_ILI9341 * gfx)
{
}

void AllSensorDataComponent::displayTemplate(Adafruit_ILI9341 * gfx)
{
    gfx->clearDisplay(); 
    gfx->setCursor(0 + x,0 + y);
	gfx->setTextSize(1);
    gfx->println("Temperature");
  
    gfx->setCursor(0 + x,10 + y);
    gfx->setTextSize(3);
    gfx->println("--.-C");
  
    gfx->setCursor(95,10);
    gfx->setTextSize(1);
    gfx->println("--.-C");
  
    gfx->setCursor(95,22);
    gfx->setTextSize(1);
    gfx->println("--.-C");

    // -------------------------------

    gfx->setTextSize(1);
    gfx->setCursor(0, 34);
    gfx->println("Humidity");
    
    gfx->setCursor(0,46);
    gfx->setTextSize(2);
    gfx->println("--.-\%");
    
     // -------------------------------
    
    gfx->setTextSize(1);
    gfx->setCursor(64, 34);
    gfx->println("Pressure");
    
    gfx->setCursor(64,46);
    gfx->setTextSize(2);
    gfx->println("----Pa");
    
//    _display.drawFastVLine(0, 33, 30, WHITE;
//    _display.drawFastHLine(0, 63, 127, WHITE);

//    gfx->_display();
}

void AllSensorDataComponent::display()
{
    _display->clearDisplay();
 
    displayTemplate(_display);

    _display->setCursor(0,10);
    _display->setTextSize(3);
    _display->println(String::format("%2.1f", _measures[TEMPERATURE_MEASURE_ID]->latestValue));
    
    _display->setCursor(95,10);
    _display->setTextSize(1);
    _display->println(String::format("%2.1f", _measures[TEMPERATURE_MEASURE_ID]->dayMax));
  
    _display->setCursor(95,22);
    _display->setTextSize(1);
    _display->println(String::format("%2.1f", _measures[TEMPERATURE_MEASURE_ID]->dayMin));

    _display->setCursor(0,46);
    _display->setTextSize(2);
    _display->println(String::format("%2.1f", _measures[HUMIDITY_MEASURE_ID]->latestValue));
    
    _display->setCursor(64,46);
    _display->setTextSize(2);
    _display->println(String::format("%4.0f", _measures[PRESSURE_MEASURE_ID]->latestValue));
    
    _display->fillRoundRect(124, 1, 2, 2, 0, ILI9341_WHITE);
   
}

