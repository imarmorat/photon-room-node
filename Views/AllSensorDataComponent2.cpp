#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "../DataCollection.h"
#include "AllSensorDataComponent2.h"
#include "Icon1.h"
#include "Component.h"
#include <math.h>

#define PI 3.14159265359
void CircleProgressBar_draw(Adafruit_ILI9341 * _display, int xc, int yc, int inner, int outer, int16_t backgroundColor, int16_t foregroundColor, float angle);

// todo: I dont like having external static used here, need to get them passed through at some point
// e.g. by passing Measures + some id

AllSensorDataComponent2::AllSensorDataComponent2(MeasureMeta* measure) : _measure(measure)
{
    /* remember to be extra careful here, had some crashes on photon when doing some init things here */
}

void AllSensorDataComponent2::display()
{
    _display->fillRect(x, y, width, height, ILI9341_BLACK);
	refresh();
}

Action AllSensorDataComponent2::handleEvent(Action action)
{
	refresh();
	return Action_None;
}

void AllSensorDataComponent2::refresh()
{
	int padding = 2;
	int xc = height / 2 + x + padding;
	int yc = height / 2 + y + padding;
	int outer = height / 2 - padding - 20;
	int inner = outer - 16;
	float min = _measure->progressBarMin; float max = _measure->progressBarMax; float value = _measure->latestValue;
	float angle = 2 * PI * (value - min) / (max - min);

	CircleProgressBar_draw(_display, xc, yc, inner, outer, ILI9341_WHITE, ILI9341_RED, angle);

	_display->setCursor(190, 40);
	_display->setTextSize(4);
	_display->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
	_display->println(String::format(_measure->format, _measure->latestValue));

	_display->setTextSize(3);
	_display->setCursor(190, 75);
	_display->println(String::format(_measure->format, _measure->dayMax));

	_display->setCursor(190, 100);
	_display->println(String::format(_measure->format, _measure->dayMin));
}
