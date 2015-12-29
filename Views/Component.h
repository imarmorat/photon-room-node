#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\general.h"

class Container;

class Component{
    public:
		uint16_t x, y, height, width;
		Container * parentContainer;

		virtual void init(Adafruit_ILI9341 * display, uint16_t x, uint16_t y, uint16_t height, uint16_t width)
		{
			this->x = x; this->y = y; this->height = height; this->width = width;
			_display = display;
		};

		virtual void display();

		virtual Action handleEvent(Action event)
		{
			// defaut behaviour
			//return event ==  ? Action_SwitchToNextView : Action_None;
			return Action_None;
		};

protected:
	Adafruit_ILI9341 * _display;
};

#endif