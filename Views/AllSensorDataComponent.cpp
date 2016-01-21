#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "Adafruit_BME280\Adafruit_BME280.h"
#include "../DataCollection.h"
#include "AllSensorDataComponent.h"
#include "Component.h"
#include "drawUtils.h"

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
	int nbColumns = MEASURE_COUNT / nbRows;

	int boxHeight = height / nbRows;
	int boxWidth = width / nbColumns;

	if (isFirstTime)
		_display->fillRect(x, y, width, height, convertRGB888toRGB565(0x303030, ILI9341_BLACK));
	
	int measureId = 0;
	for (int i = 0; i < nbColumns; i++)
		for (int j = 0; j < nbRows; j++)
		{
			displayMeasure(_display, isFirstTime, x + boxWidth * i, y + boxHeight * j, boxWidth, boxHeight, measureId < MEASURE_COUNT ? _measures[measureId] : NULL);
			measureId++;
		}
}

void AllSensorDataComponent::displayMeasure(Adafruit_ILI9341* display, bool isFirstTime, int x, int y, int width, int height, MeasureMeta * measure)
{
	if (measure == NULL)
		return;

	int nbComponents = 3; // short name, icon and value
	int textHeight = 14; int iconHeight = 32; int charWidth = 10;
	int padding = (height - (textHeight * 2 + iconHeight)) / (nbComponents + 1);

	if (isFirstTime)
		display->fillRect(x, y, width, height, convertRGB888toRGB565(0x050505));
	
	int yi = y + padding;

	display->setTextSize(2);
	display->setTextColor(convertRGB888toRGB565(0x353535), convertRGB888toRGB565(0x050505));

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
		if (measure->iconData32 != NULL)
		{
			drawBitmap(display, x + width / 2 - iconHeight / 2, yi, iconHeight, iconHeight, measure->iconData32);
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
		display->fillRect(x, yi, width, textHeight, convertRGB888toRGB565(0x050505));
	
	String  value = String::format(measure->format, measure->latestValue);
	display->setTextColor(ILI9341_GREEN, convertRGB888toRGB565(0x050505));
	display->setCursor(x + width / 2 - value.length()*charWidth/2, yi);
	display->println(value);
}

