#ifndef _ALARMCOMPONENT_H
#define _ALARMCOMPONENT_H

#include "Component.h"
#include "Container.h"

class AlarmComponent : public Component
{
public:
	AlarmComponent(MeasureMeta ** measures);
	void display();
	Action handleEvent(Action action);
	void refresh();

private:
	MeasureMeta ** _measures;
};

#endif