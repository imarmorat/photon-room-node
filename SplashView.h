#ifndef _SPLASHVIEW_H
#define _SPLASHVIEW_H

#include "application.h"
#include "View.h"

class SplashView : public View
{
    public:
        void display(Adafruit_SSD1306 * display);
};

#endif