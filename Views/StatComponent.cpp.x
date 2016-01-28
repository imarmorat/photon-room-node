#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "StatComponent.h"
#include "application.h"


void StatComponent::begin()
{

}

void StatComponent::display()
{
    float min = 0.0;
    float max = 30.0;
    
    for(int i=0; i<24*4; i++)
        stats[i] = (float) random(22,25);
    
    _display->clearDisplay();
    _display->drawFastVLine(10, 0, 64, ILI9341_WHITE);
    _display->drawFastHLine(10, 63, 118, ILI9341_WHITE);
    _display->setTextSize(1);
    _display->setCursor(0,0);
    _display->printf("%2.0f", max);
    
    _display->setCursor(0, 64-8);
    _display->printf("%2.0f", min);

    _display->setRotation(3);
    _display->setCursor(20,0); // coordinates are rotated    
    _display->printf("TMP");
    
    _display->setRotation(0);
    
    // render graph
    unsigned char startX = 12;
    unsigned char startY = 62;
    for(int i=0; i<24*4; i++)
    {
        float val = 62.0 * (max - stats[i])/(max-min);
        _display->drawPixel(startX + (i*2), val, ILI9341_WHITE);
        _display->drawPixel(startX + (i*2) + 1, val, ILI9341_WHITE);
        //_display->drawFastVLine(startX + (i*2), val, 62.0-val, WHITE);
        //_display->drawFastVLine(startX + (i*2) + 1, val, 62.0-val, WHITE);
    }
    
   // _display->_display();
    
}