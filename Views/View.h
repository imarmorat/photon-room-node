#ifndef _VIEW_H
#define _VIEW_H

#include "..\general.h"

class View{
    public:
        virtual void display(Adafruit_ILI9341 * display);
		virtual Action handleInput(BoardInput input)
		{
			// defaut behaviour
			return input == BoardInput_Button1 ? Action_SwitchToNextView : Action_None;
		};
};

#endif