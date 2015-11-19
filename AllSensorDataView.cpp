#include "Adafruit_SSD1306\Adafruit_SSD1306.h"
#include "Adafruit_BME280/Adafruit_BME280.h"
#include "SensorDataManager.h"
#include "AllSensorDataView.h"
#include "View.h"

bool showHeartbeat = false;

AllSensorDataView::AllSensorDataView()
{
    /* remember to be extra careful here, had some crashes on photon when doing some init things here */
}

void AllSensorDataView::begin(Adafruit_SSD1306 * gfx, SensorDataManager * sdm)
{
    _sdm = sdm;
}

void displayTemplate(Adafruit_SSD1306 * gfx)
{
    gfx->clearDisplay(); 
    gfx->setCursor(0,0);
    gfx->println("Temperature");
  
    gfx->setCursor(0,10);
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
    
//    display.drawFastVLine(0, 33, 30, WHITE;
//    display.drawFastHLine(0, 63, 127, WHITE);

//    gfx->display();
}

void AllSensorDataView::display(Adafruit_SSD1306 * display)
{
    display->clearDisplay();
 
    displayTemplate(display);
 
    if (showHeartbeat)
    {
        display->drawRect(122, 1, 2, 2, WHITE);
        display->display();
    }

    _sdm->updateSensorData();

    display->setCursor(0,10);
    display->setTextSize(3);
    display->println(String::format("%2.1f", _sdm->_temperature.current));
    
    display->setCursor(95,10);
    display->setTextSize(1);
    display->println(String::format("%2.1f", _sdm->_temperature.max));
  
    display->setCursor(95,22);
    display->setTextSize(1);
    display->println(String::format("%2.1f", _sdm->_temperature.min));

    display->setCursor(0,46);
    display->setTextSize(2);
    display->println(String::format("%2.1f", _sdm->_humidity.current));
    
    display->setCursor(64,46);
    display->setTextSize(2);
    display->println(String::format("%4.0f", _sdm->_pressure.current));
    
    display->fillRoundRect(124, 1, 2, 2, 0, WHITE);
    
    display->display();
    
    if (showHeartbeat)
    {
        delay(500);
        display->drawRect(124, 1, 2, 2, BLACK);
        display->drawRect(122, 1, 2, 2, BLACK);
        display->display();
    }
}

