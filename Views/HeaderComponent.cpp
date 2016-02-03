#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "HeaderComponent.h"
#include "application.h"

#define BACKGROUND_COLOR ILI9341_BLACK
#define FOREGROUND_COLOR ILI9341_YELLOW

void displayTime(Adafruit_ILI9341 * display, int padding, int x, int y, uint16_t fgColor, uint16_t bgColor)
{
	display->setCursor(x + padding, y + padding);
	display->setTextSize(2);
	display->setTextColor(fgColor, bgColor);
	display->println(Time.format(Time.now(), "%H:%M %a %d-%b"));
}

void displayDataCollectionIndicator(Adafruit_ILI9341 * display, int padding, bool isOn, uint16_t fgColor, uint16_t bgColor)
{
	display->fillRect(320 - padding - 5, padding, 5, 5, isOn ? fgColor : bgColor);
}

void displayWifiStatus(Adafruit_ILI9341 * display, uint16_t fgColor, uint16_t bgColor)
{
	bool isReady = WiFi.ready();
	int signalQuality = WiFi.RSSI(); // returns a value between -127 and -1
	float signalInPercent = 100.0 * (signalQuality + 127.0) / (127.0 - 1.0);

	display->setTextColor(fgColor, bgColor);
	display->setCursor(200, 3);
	display->println(isReady ? String::format("%3.0f", signalInPercent) : "N/A");
}

static uint16_t getFgColor(Alarm * alarm)
{
	MeasureZone alarmLevel = alarm->CheckForAlerts();
	switch (alarmLevel)
	{
	case MeasureZone_Normal: return FOREGROUND_COLOR;
	case MeasureZone_Warning: return ALARM_WARNING_COLOR_FG;
	case MeasureZone_Critical: return ALARM_CRITICAL_COLOR_FG;
	}

	return FOREGROUND_COLOR;
}

static uint16_t getBgColor(Alarm * alarm)
{
	MeasureZone alarmLevel = alarm->CheckForAlerts();
	switch (alarmLevel)
	{
	case MeasureZone_Normal: return BACKGROUND_COLOR;
	case MeasureZone_Warning: return ALARM_WARNING_COLOR_BG;
	case MeasureZone_Critical: return ALARM_CRITICAL_COLOR_BG;
	}

	return BACKGROUND_COLOR;
}


HeaderComponent::HeaderComponent()
{
	height = 20;
	width = 320;
	x = 0;
	y = 0;
}

void HeaderComponent::setup(Alarm * alarm)
{
	_alarm = alarm;
}

void HeaderComponent::display()
{
	uint16_t bgColor = getBgColor(_alarm);
	uint16_t fgColor = getFgColor(_alarm);

	_display->fillRect(x, y, width, height, bgColor);
	displayTime(_display, 3, x, y, fgColor, bgColor);
	displayDataCollectionIndicator(_display, 3, true, fgColor, bgColor);
	displayWifiStatus(_display, fgColor, bgColor);
	// nb of errors and warning
}

Action HeaderComponent::handleEvent(Action action)
{
	uint16_t bgColor = getBgColor(_alarm);
	uint16_t fgColor = getFgColor(_alarm);

	displayTime(_display, 3, x, y, fgColor, bgColor);
	displayWifiStatus(_display, fgColor, bgColor);

	if (action == Event_MeasureCollectionStarted)
		displayDataCollectionIndicator(_display, 3, true, fgColor, bgColor);

	if (action == Event_MeasureCollectionCompleted)
		displayDataCollectionIndicator(_display, 3, false, fgColor, bgColor);

	return Action_None;
}

