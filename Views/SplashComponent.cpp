#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "SplashComponent.h"
#include "../Adafruit_mfGFX/fonts.h"

void SplashComponent::display()
{
	_display->fillRect(x, y, width, height, ILI9341_BLACK);

	byte mac[6];
	WiFi.macAddress(mac);

	_display->setCursor(x, y);
	_display->setTextSize(2);
	_display->setTextColor(ILI9341_WHITE, ILI9341_BLACK);

	_display->println(WiFi.SSID());
	_display->println(WiFi.localIP());
	for (int i = 0; i <= 5; i++)
	{
		if (i)
			_display->print(":");
		_display->print(mac[i], HEX);
	}
	_display->println("");
	_display->println(String::format("Ver: %s", System.version().c_str()));
	_display->println(String::format("Free mem:%d", System.freeMemory()));
	//_display.println(String::format("DID: %s", System.deviceID()));
}