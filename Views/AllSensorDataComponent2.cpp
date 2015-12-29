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

AllSensorDataComponent2::AllSensorDataComponent2(MeasureMeta** measures) : _measures(measures)
{
    /* remember to be extra careful here, had some crashes on photon when doing some init things here */
}

void AllSensorDataComponent2::display()
{
    _display->fillRect(x, y, width, height, ILI9341_BLACK);

	MeasureMeta* currentMeasure = _measures[0];

	int padding = 5;
	int xc = height/2 + x + padding;
	int yc = height/2 + y + padding;
	int outer = height/2 - padding - 20;
	int inner = outer - 10;
	Particle.publish("debug", String::format("%d %d %d %d", xc, yc, inner, outer));
	int min = 0; int max = 100; int value = 95;
	int angle = 2 * PI * (value - min) / (max - min);

	CircleProgressBar_draw(_display, xc, yc, inner, outer, ILI9341_WHITE, ILI9341_RED, angle);

	//uint16_t colors[3]; colors[0] = ILI9341_BLACK; colors[1] = ILI9341_BLACK + 10; colors[2] = ILI9341_BLACK + 20; int colorIndex = 0;
	//int h = 240;
	//int w = 320;
	//int nbCol = 2; int colWidth = w / nbCol;
	//int nbRow = 2; int rowHeight = h / nbRow;
	//int padding = 4;
	//	//draw_arc(_display, 100, 100, 50, 50, 0, 5, ILI9341_WHITE, 5);

	//for (int x = 0; x < w; x += colWidth)
	//	for (int y = 0; y < h; y += rowHeight)
	//	{
	//		//_display->fillRect(x, y, colWidth, rowHeight, colors[colorIndex++ % 3]);
	//		_display->setCursor(x + padding, y + padding);
	//		_display->setTextColor(ILI9341_WHITE);
	//		_display->setTextSize(3);
	//		_display->println("24");

	//		_display->drawFastVLine(x + padding  + 40, y + padding, rowHeight - 10, ILI9341_WHITE);
	//		
	//		_display->setTextSize(2);
	//		_display->setCursor(x + padding + 50, y + padding);
	//		_display->setTextColor(ILI9341_RED);
	//		_display->println("28.5 C");

	//		_display->setTextSize(2);
	//		_display->setCursor(x + padding + 50, y + padding + 20);
	//		_display->setTextColor(ILI9341_GREEN);
	//		_display->println("22.5 C");

	//	}
}
