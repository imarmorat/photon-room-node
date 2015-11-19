#include "Adafruit_SSD1306\Adafruit_SSD1306.h"
#include "StatView.h"

#include "application.h"
//#include "Adafruit_SSD1306/Adafruit_SSD1306.h"


float stats[24*4];

void StatView::begin()
{

}

void StatView::display(Adafruit_SSD1306 * display)
{
    float min = 0.0;
    float max = 30.0;
    
        for(int i=0; i<24*4; i++)
        stats[i] = (float) random(22,25);
    
    display->clearDisplay();
    display->drawFastVLine(10, 0, 64, WHITE);
    display->drawFastHLine(10, 63, 118, WHITE);
    display->setTextSize(1);
    display->setCursor(0,0);
    display->printf("%2.0f", max);
    
    display->setCursor(0, 64-8);
    display->printf("%2.0f", min);

    display->setRotation(3);
    display->setCursor(20,0); // coordinates are rotated    
    display->printf("TMP");
    
    display->setRotation(0);
    
    // render graph
    unsigned char startX = 12;
    unsigned char startY = 62;
    for(int i=0; i<24*4; i++)
    {
        float val = 62.0 * (max - stats[i])/(max-min);
        display->drawPixel(startX + (i*2), val, WHITE);
        display->drawPixel(startX + (i*2) + 1, val, WHITE);
        //display->drawFastVLine(startX + (i*2), val, 62.0-val, WHITE);
        //display->drawFastVLine(startX + (i*2) + 1, val, 62.0-val, WHITE);
    }
    
    display->display();
    
}