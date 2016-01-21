#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "general.h"
#include "DataCollection.h"
#include "Alarm.h"
#include "Views\drawUtils.h"

//#define nbMeasures sizeof(_measures)/sizeof(MeasureMeta*)

Alarm::Alarm(int buzzerPin, Adafruit_ILI9341 * display)
{
	_display = display;
	_buzzerPin = buzzerPin;
}

void Alarm::Init(MeasureMeta ** measures)
{
	_measures = measures;
	pinMode(_buzzerPin, OUTPUT);
	digitalWrite(_buzzerPin, LOW);
}

// returns the highest level of error
MeasureZone Alarm::CheckForAlerts()
{
	int nbCriticals = GetLevelCount(MeasureZone_Critical);
	int nbWarnings = GetLevelCount(MeasureZone_Warning);

	if (nbCriticals > 0)
		return MeasureZone_Critical;

	if (nbWarnings > 0)
		return MeasureZone_Warning;

	return MeasureZone_Normal;
}

int Alarm::GetLevelCount(MeasureZone level)
{
	int count = 0;
	for (int i = 0; i < MEASURE_COUNT; i++)
		if (_measures[i]->latestLevel == level) 
			count++;

	return count;
}

void Alarm::TriggerAlarm()
{
	if (_isOn)
		return;

	_isOn = true;

	//
	// finally, display and ring the bell
	//tone(_buzzerPin, 2555, 0); // https://docs.particle.io/reference/firmware/core/#tone-
	digitalWrite(_buzzerPin, HIGH);
	DisplayAlerts();

	Particle.publish("events.alarm.status", "on");
}

void Alarm::DisableAlarm()
{
	if (!_isOn)
		return;

	//noTone(_buzzerPin);
	digitalWrite(_buzzerPin, LOW);
	_isOn = false;

	Particle.publish("events.alarm.status", "off");
}

bool Alarm::IsTriggered()
{
	return _isOn;
}

void Alarm::DisplayAlerts()
{
	int nbCritical = GetLevelCount(MeasureZone_Critical);
	int nbWarning = GetLevelCount(MeasureZone_Warning);

	//
	// big text alert
	int messageBoxHeight = 240 / 2;
	uint16_t mainBgColor = nbCritical != 0 ? ILI9341_RED : 0xFD20;
	_display->fillRect(0, 0, 320, messageBoxHeight, mainBgColor);
	int textSize = 4; int textHeight = 28;
	String message = nbCritical > 0 ? "CRITICAL" : "WARNING";
	int textX = (320 - message.length() * textSize * 5) / 2; // 320 - (ALERT!!.length * charWidth)
	int textY = (messageBoxHeight - textHeight) / 2;

	_display->setCursor(textX, textY); 
	_display->setTextSize(textSize);
	_display->setTextColor(ILI9341_WHITE, mainBgColor);
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
	int measureBoxWidth = (measureCoutainerWidth - measureBoxMargin*boxCount) / (boxCount);
	int measureBoxHeight = measureCoutainerHeight - measureBoxMargin*2; // 5px padding
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
		uint16_t boxBgColor = _measures[i]->latestLevel == MeasureZone_Critical ? ILI9341_RED : 0xFD20;
		_display->fillRect(xi, yi, measureBoxWidth, measureBoxHeight, boxBgColor);

		// header
		yj += verticalSpacing;
		_display->setTextColor(ILI9341_WHITE, boxBgColor);
		_display->setCursor(xi + measureBoxWidth / 2 - _measures[i]->shortName.length() * charWidth * headerTextSize / 2, yj);
		_display->println(_measures[i]->shortName);

		//
		// icon
		yj += verticalSpacing + 7 * headerTextSize;
		drawBitmap(_display, xi + measureBoxWidth / 2 - iconSize / 2, yj, iconSize, iconSize, _measures[i]->iconData32);

		//
		// latest value
		yj += verticalSpacing + iconSize;
		String  value = String::format(_measures[i]->format, _measures[i]->latestValue);
		_display->setTextColor(ILI9341_WHITE, boxBgColor);
		_display->setCursor(xi + measureBoxWidth / 2 - value.length() * charWidth * latestValueTextSize / 2, yj);
		_display->println(value);

		xi += measureBoxMargin + measureBoxWidth;
	}

	// todo: display useful information
}