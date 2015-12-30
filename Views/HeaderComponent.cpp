#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "HeaderComponent.h"
#include "application.h"

#define BACKGROUND_COLOR ILI9341_BLACK
#define FOREGROUND_COLOR ILI9341_YELLOW



void displayTime(Adafruit_ILI9341 * display, int padding, int x, int y)
{
	display->setCursor(x + padding, y + padding);
	display->setTextSize(1);
	display->setTextColor(FOREGROUND_COLOR, BACKGROUND_COLOR);
	display->println(Time.format(Time.now(), "%H:%M %a %d-%b"));
}

void displayDataCollectionIndicator(Adafruit_ILI9341 * display, int padding, bool isOn)
{
	display->fillRect(320 - padding - 5, padding, 5, 5, isOn ? FOREGROUND_COLOR : BACKGROUND_COLOR);
}

void displayWifiStatus(Adafruit_ILI9341 * display)
{
	bool isReady = WiFi.ready();
	int signalQuality = WiFi.RSSI(); // returns a value between -127 and -1
	float signalInPercent = 100.0 * (signalQuality + 127.0) / (127.0 - 1.0);

	display->setCursor(200, 3);
	display->println(isReady ? String::format("%3.0f", signalInPercent) : "N/A");
}


HeaderComponent::HeaderComponent()
{
	height = 20;
	width = 320;
	x = 0;
	y = 0;
}

void HeaderComponent::display()
{
	_display->fillRect(x, y, width, height, BACKGROUND_COLOR);
	displayTime(_display, 3, x, y);
	displayDataCollectionIndicator(_display, 3, true);
	displayWifiStatus(_display);
	// wifi signal + connection status
	// time
	// nb of errors and warning
	// data collecction indicator
}

Action HeaderComponent::handleEvent(Action action)
{
	displayTime(_display, 3, x, y);
	displayWifiStatus(_display);

	if (action == Event_MeasureCollectionStarted)
		displayDataCollectionIndicator(_display, 3, true);

	if (action == Event_MeasureCollectionCompleted)
		displayDataCollectionIndicator(_display, 3, false);

	return Action_None;
}

