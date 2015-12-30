#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "../DataCollection.h"
#include "AllSensorDataComponent2.h"
//#include "Icon1.h"
#include "Component.h"
#include <math.h>

#include "icons\humidity-icon-64.h"
#include "..\utils.h"

#define PI 3.14159265359
void CircleProgressBar_draw(Adafruit_ILI9341 * _display, int xc, int yc, int inner, int outer, int16_t backgroundColor, int16_t foregroundColor, float angle);

static uint8_t getAlpha(int color) { return (color & 0xff000000) >> 24; }
static uint8_t getRed(int color) { return (color & 0x00ff0000) >> 16; }
static uint8_t getBlue(int color) { return (color & 0x0000ff00) >> 8; }
static uint8_t getGreen(int color) { return (color & 0x000000ff); }

static uint16_t convertRGB888toRGB565(int color, int background)
{
	// color is ARGB
	//
	// remove alpha
	uint8_t alpha = getAlpha(color);
	alpha = 0xff;
	float diff = 1.0 - alpha / 255.0;

	uint8_t red = (getRed(color) * (1 - diff)) + getRed(background) * diff;
	uint8_t blue = (getBlue(color) * (1 - diff)) + getBlue(background) * diff;
	uint8_t green = (getGreen(color) * (1 - diff)) + getGreen(background) * diff;

	return (((31 * (red + 4)) / 255) << 11) | (((63 * (green + 2)) / 255) << 5) | ((31 * (blue + 4)) / 255);
}



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
	int xc = height / 2 + x + padding - 15;
	int yc = height / 2 + y + padding;
	int outer = height / 2 - padding - 25;
	int inner = outer - 14;
	float min = _measure->progressBarMin; float max = _measure->progressBarMax; float value = _measure->latestValue;
	float angle = 2 * PI * (value - min) / (max - min);

	CircleProgressBar_draw(_display, xc, yc, inner, outer, 0x1082, 0x0210, angle);

	_display->setCursor(190, 40);
	_display->setTextSize(4);
	_display->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
	_display->println(String::format(_measure->format, _measure->latestValue));

	_display->setTextSize(3);
	_display->setCursor(190, 75);
	_display->println(String::format(_measure->format, _measure->dayMax));

	_display->setCursor(190, 100);
	_display->println(String::format(_measure->format, _measure->dayMin));

	int iconX = xc - _measure->iconHeight / 2;
	int iconY = yc - _measure->iconWidth / 2;

	for (int i = 0; i < _measure->iconHeight; i++)
		for (int j = 0; j < _measure->iconWidth; j++)
			_display->drawPixel(iconX + i, iconY + j, convertRGB888toRGB565(_measure->iconData[i * _measure->iconWidth + j], 0));


}
