#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "SplashView.h"

void SplashView::display(Adafruit_ILI9341 * display)
{
    byte mac[6];
    WiFi.macAddress(mac);
    
    display->clearDisplay();
    display->setCursor(0,0);
    display->setTextSize(1);
    display->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    
    display->println(WiFi.SSID());
    display->println(WiFi.localIP());
    for(int i=0;i<=5;i++)
    {
        if (i)
            display->print(":");
        display->print(mac[i], HEX);
    }
    display->println("");
    display->println(String::format("Ver: %s", System.version().c_str()));
    display->println(String::format("Free mem:%d", System.freeMemory()));
    //display.println(String::format("DID: %s", System.deviceID()));
    
    //display->display();
}