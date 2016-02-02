#ifndef _ALLSENSORDATAVIEW_H
#define _ALLSENSORDATAVIEW_H

#include "Component.h"
#include "Container.h"

class AllSensorDataComponent : public Component
{
    public:
		AllSensorDataComponent(MeasureMeta** measures);
		void display();
		Action handleEvent(Action action);
		void refresh();

private:
	MeasureMeta** _measures;
	void displayMeasure(Adafruit_ILI9341* display, bool isFirstTime, int x, int y, int width, int height, MeasureMeta * measure, uint16_t bgColor);
	void draw(bool isFirstTime);
};

#endif