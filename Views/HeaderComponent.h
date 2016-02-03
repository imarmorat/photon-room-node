#ifndef __HEADERCOMPONENT_H_
#define __HEADERCOMPONENT_H_

#include "Component.h"
#include "Container.h"
#include "..\Alarm.h"

class HeaderComponent : public Component
{
public:
	HeaderComponent();
	void setup(Alarm * alarm);
	void display();
	uint16_t x, y, height, width;
	Container * parentContainer;
	Action handleEvent(Action action);

private:
	Alarm * _alarm;
};

#endif
