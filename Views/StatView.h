#ifndef _STATVIEW_H
#define _STATVIEW_H
#include "View.h"

enum StatViewMode { Pressure, Temperature, Humidity };

class StatView : public View
{
  public:
    StatViewMode Mode;
    void begin();
    void display(Adafruit_ILI9341 * display);
};

#endif