#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "../DataCollection.h"
#include "AllSensorDataComponent2.h"
#include "Component.h"
#include <math.h>
#include "..\utils.h"

#include "icons\arrowdown-icon-24.h"
#include "icons\arrowup-icon-24.h"

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
	if (action == Event_MeasureCollectionCompleted)
		refresh();

	return Action_None;
}

static void drawBitmap(Adafruit_ILI9341* display, int x, int y, int height, int width, const unsigned int * bitmap)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			display->drawPixel(x + i, y + j, convertRGB888toRGB565(bitmap[i * width + j], 0));
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


	CircleProgressBar_draw(_display, xc, yc, inner, outer, -1, 0x0210, angle);
	//CircleProgressBar_draw(_display, xc, yc, inner, outer, 0x1082, 0x0210, angle);

	_display->setCursor(180, 40);
	_display->setTextSize(4);
	_display->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
	_display->println(String::format(_measure->format, _measure->latestValue));
	_display->drawFastHLine(180, 75, 130, 0x1082);

	_display->setTextSize(3);
	_display->setCursor(180 + arrowupIcon_width + 3, 80);
	_display->println(String::format(_measure->format, _measure->dayMax));
	drawBitmap(_display, 180, 80, arrowupIcon_height, arrowupIcon_width, &arrowupIcon[0]);

	_display->setCursor(180 + arrowupIcon_width + 3, 110);
	_display->println(String::format(_measure->format, _measure->dayMin));
	drawBitmap(_display, 180, 110, arrowdownIcon_height, arrowdownIcon_width, &arrowdownIcon[0]);

	drawBitmap(_display, xc - _measure->iconHeight / 2, yc - _measure->iconWidth / 2, _measure->iconHeight, _measure->iconWidth, &_measure->iconData[0]);
	

	//
	// GRAPH
	int graphX = 180;
	int graphY = 140;
	int graphHeight = 78;
	int graphWidth = 130;
	float graphMin = _measure->progressBarMin; float graphMax = _measure->progressBarMax;
	_display->fillRect(graphX, graphY, graphWidth, graphHeight, ILI9341_BLACK);


	// draw axis
	_display->drawFastVLine(graphX, graphY, graphHeight, ILI9341_WHITE);
	_display->drawFastHLine(graphX, graphY + graphHeight, graphWidth, ILI9341_WHITE);

	float statsMin[24];
	float statsAvg[24];
	float statsMax[24];
	float bucketCount = 24.0;
	int bucketPixelSize = graphWidth / bucketCount;

	for (int i = 0; i < bucketCount; i++)
	{
		statsMin[i] = (float)random(15, 20);
		statsAvg[i] = (float)random(22, 25);
		statsMax[i] = (float)random(25, 30);
	}

	// render graph
	for (int i = 0; i<bucketCount; i++)
	{
		float minVal = graphHeight * (graphMax - statsMin[i]) / (graphMax - graphMin);
		float avgVal = graphHeight * (graphMax - statsAvg[i]) / (graphMax - graphMin);
		float maxVal = graphHeight * (graphMax - statsMax[i]) / (graphMax - graphMin);

		for (int j = 0; j < bucketPixelSize; j++)
		{
			int x = (i * bucketPixelSize) + graphX +1; // +1 to not erase vertical axis
			_display->drawFastVLine(x + j, graphY + maxVal, minVal - maxVal, 0x1082);
			_display->drawPixel(x + j, graphY + avgVal, 0x0210);
		}
	}

}
