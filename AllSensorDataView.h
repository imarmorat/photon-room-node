#ifndef _ALLSENSORDATAVIEW_H
#define _ALLSENSORDATAVIEW_H
#include "View.h"

class AllSensorDataView : public View
{
    public:
        AllSensorDataView();
        void begin(Adafruit_SSD1306 * gfx, SensorDataManager * sdm);
        void display(Adafruit_SSD1306 * gfx);
        
    private:
        SensorDataManager * _sdm;
};

#endif