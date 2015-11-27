#include "Adafruit_SSD1306\Adafruit_SSD1306.h"
#include "SplashView.h"

void SplashView::display(Adafruit_SSD1306 * display)
{
    byte mac[6];
    WiFi.macAddress(mac);
    
    display->clearDisplay();
    display->setCursor(0,0);
    display->setTextSize(1);
    display->setTextColor(WHITE, BLACK);
    
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
    
    display->display();
}