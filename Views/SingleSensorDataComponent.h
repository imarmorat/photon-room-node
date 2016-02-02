#ifndef _SINGLESENSORDATACOMPONENT_H
#define _SINGLESENSORDATACOMPONENT_H
#include "Component.h"

class SingleSensorDataComponent : public Component
{
    public:
		SingleSensorDataComponent(MeasureMeta* measure);
        void display();
		Action handleEvent(Action action);
		void refresh();

	private:
		MeasureMeta* _measure;
};

#endif