#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "../DataCollection.h"
#include "AllSensorDataComponent.h"
#include "Component.h"
#include "drawUtils.h"
#include "../Alarm.h"
#include "AlarmComponent.h"

#define CRITICAL_COLOR_BG ILI9341_RED
#define CRITICAL_COLOR_FG ILI9341_WHITE
#define WARNING_COLOR_BG 0xFA20
#define WARNING_COLOR_FG ILI9341_WHITE

AlarmComponent::AlarmComponent(MeasureMeta ** measures)
{
	_measures = measures;
}

void AlarmComponent::display()
{
	int nbCritical = Alarm::GetLevelCount(_measures, MeasureZone_Critical);
	int nbWarning = Alarm::GetLevelCount(_measures, MeasureZone_Warning);

	//
	// big text alert
	int messageBoxHeight = 240 / 2;
	uint16_t mainBgColor = nbCritical != 0 ? CRITICAL_COLOR_BG : WARNING_COLOR_BG;
	uint16_t mainFgColor = nbCritical != 0 ? CRITICAL_COLOR_FG : WARNING_COLOR_FG;
	_display->fillRect(0, 0, 320, messageBoxHeight, mainBgColor);
	int textSize = 4; int textHeight = 28;
	String message = nbCritical > 0 ? "CRITICAL" : "WARNING";
	int textX = (320 - message.length() * textSize * 5) / 2; // 320 - (ALERT!!.length * charWidth)
	int textY = (messageBoxHeight - textHeight) / 2;

	_display->setCursor(textX, textY);
	_display->setTextSize(textSize);
	_display->setTextColor(mainFgColor, mainBgColor);
	_display->println(message);

	//
	// Display measure info for those who have warnings or error
	_display->fillRect(0, messageBoxHeight, 320, 240 - messageBoxHeight, convertRGB888toRGB565(0x050505));
	_display->setTextSize(2);
	int measureContainerX = 0;
	int measureCoutainerY = 240 / 2;
	int measureCoutainerWidth = 320 - measureContainerX;
	int measureCoutainerHeight = 240 - measureCoutainerY;

	int measureBoxMargin = 5;
	int measureBoxPadding = 2;
	int boxCount = nbCritical + nbWarning;
	int measureBoxWidth = (measureCoutainerWidth - measureBoxMargin*(boxCount + 1)) / (boxCount);
	int measureBoxHeight = measureCoutainerHeight - measureBoxMargin * 2; // 5px padding
	int headerTextSize = 2;
	int charWidth = 5;
	int iconSize = 32;
	int latestValueTextSize = 2;
	int verticalSpacing = (measureBoxHeight - (headerTextSize * 7 + iconSize + latestValueTextSize * 7)) / (3 + 1); // 3 layout item => 4 spaces

	int xi = measureContainerX + measureBoxMargin;
	int yi = measureCoutainerY + measureBoxMargin;
	for (int i = 0; i < MEASURE_COUNT; i++)
	{
		if (_measures[i]->latestLevel == MeasureZone_Normal)
			continue;

		int yj = yi;
		uint16_t boxBgColor = _measures[i]->latestLevel == MeasureZone_Critical ? CRITICAL_COLOR_BG : WARNING_COLOR_BG;
		_display->fillRect(xi, yi, measureBoxWidth, measureBoxHeight, boxBgColor);

		// header
		yj += verticalSpacing;
		_display->setTextColor(mainFgColor, boxBgColor);
		_display->setCursor(xi + measureBoxWidth / 2 - _measures[i]->shortName.length() * charWidth * headerTextSize / 2, yj);
		_display->println(_measures[i]->shortName);

		//
		// icon
		yj += verticalSpacing + 7 * headerTextSize;
		drawBitmap(_display, xi + measureBoxWidth / 2 - iconSize / 2, yj, iconSize, iconSize, _measures[i]->icon32);

		//
		// latest value
		yj += verticalSpacing + iconSize;
		String  value = String::format(_measures[i]->format, _measures[i]->latestValue);
		_display->setTextColor(mainFgColor, boxBgColor);
		_display->setCursor(xi + measureBoxWidth / 2 - value.length() * charWidth * latestValueTextSize / 2, yj);
		_display->println(value);

		xi += measureBoxMargin + measureBoxWidth;
	}
}

void AlarmComponent::refresh()
{
	display();
}

Action AlarmComponent::handleEvent(Action action)
{
	if (action == Event_Button1Pressed)
		return Event_StopAlarmRequested;

	return Action_None;
}