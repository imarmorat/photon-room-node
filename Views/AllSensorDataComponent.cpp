#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "../DataCollection.h"
#include "AllSensorDataComponent.h"
#include "Component.h"
#include "drawUtils.h"
#include <math.h>

AllSensorDataComponent::AllSensorDataComponent(MeasureMeta** measures) : _measures(measures)
{
    /* remember to be extra careful here, had some crashes on photon when doing some init things here */
}

void AllSensorDataComponent::display()
{
	draw(true);
}

void AllSensorDataComponent::refresh()
{
	draw(false);
}

Action AllSensorDataComponent::handleEvent(Action action)
{
	if (action == Event_MeasureCollectionCompleted)
		refresh();

	return Action_None;
}

void AllSensorDataComponent::draw(bool isFirstTime)
{
	int nbRows = 2;
	int nbColumns = MEASURE_COUNT / nbRows + (MEASURE_COUNT % nbRows != 0); // the modulo is a trick to round up

	int boxHeight = height / nbRows;
	int boxWidth = width / nbColumns;
	uint16_t bgColor = convertRGB888toRGB565(0x050505);

	if (isFirstTime)
		_display->fillRect(x, y, width, height, bgColor);
	
	int measureId = 0;
	for (int i = 0; i < nbColumns; i++)
		for (int j = 0; j < nbRows; j++)
		{
			if (measureId >= MEASURE_COUNT)
			{
				_display->fillRect(x + boxWidth * i, y + boxHeight * j, boxWidth, boxHeight, bgColor);
				return;
			}
			else
			{
				displayMeasure(_display, isFirstTime, x + boxWidth * i, y + boxHeight * j, boxWidth, boxHeight, measureId < MEASURE_COUNT ? _measures[measureId] : NULL, bgColor);
				measureId++;
			}
		}
}

void AllSensorDataComponent::displayMeasure(Adafruit_ILI9341* display, bool isFirstTime, int x, int y, int width, int height, MeasureMeta * measure, uint16_t bgColor)
{
	if (measure == NULL)
		return;

	int nbComponents = 3; // short name, icon and value
	int textHeight = 14; int iconHeight = 32; int charWidth = 10;
	int padding = (height - (textHeight * 2 + iconHeight)) / (nbComponents + 1);
	uint16_t meausureNameColor = convertRGB888toRGB565(0x353535);
	uint16_t measureValueColor = ILI9341_GREEN;

	if (isFirstTime)
		display->fillRect(x, y, width, height, bgColor);
	
	int yi = y + padding;

	display->setTextSize(2);
	display->setTextColor(meausureNameColor, bgColor);

	// short name
	if (isFirstTime)
	{
		display->setCursor(x + width / 2 - measure->shortName.length()*charWidth/2, yi);
		display->println(measure->shortName);
	}

	// icon
	yi += padding + textHeight;

	if (isFirstTime)
	{
		if (measure->icon32 != NULL)
		{
			drawBitmap(display, x + width / 2 - iconHeight / 2, yi, iconHeight, iconHeight, measure->icon32, bgColor);
		}
		else
		{
			display->fillRect(x + width / 2 - iconHeight / 2, yi, iconHeight, iconHeight, ILI9341_BLACK);
		}
	}

	// value
	yi += padding + iconHeight;
	
	if (!isFirstTime)
		// need to erase previous content as might leave leftovers
		display->fillRect(x, yi, width, textHeight, bgColor);
	
	String  value = String::format(measure->format, measure->latestValue);
	display->setTextColor(measureValueColor, bgColor);
	display->setCursor(x + width / 2 - value.length()*charWidth/2, yi);
	display->println(value);
}

