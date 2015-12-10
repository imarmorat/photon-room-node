#ifndef _ALLSENSORDATAVIEW_H
#define _ALLSENSORDATAVIEW_H
#include "View.h"

class AllSensorDataView : public View
{
    public:
        AllSensorDataView(MeasureMeta** measures);
        void begin(Adafruit_ILI9341 * gfx);
        void display(Adafruit_ILI9341 * gfx);
	private:
		MeasureMeta** _measures;
};

#endif