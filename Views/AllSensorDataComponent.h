#ifndef _ALLSENSORDATAVIEW_H
#define _ALLSENSORDATAVIEW_H

#include "Component.h"
#include "Container.h"

class AllSensorDataComponent : public Component
{
    public:
		AllSensorDataComponent(MeasureMeta** measures);
        void begin(Adafruit_ILI9341 * gfx);
        void display();
	private:
		MeasureMeta** _measures;
		void displayTemplate(Adafruit_ILI9341 * gfx);
};

#endif