#ifndef _ALLSENSORDATACOMPONENT2_H
#define _ALLSENSORDATACOMPONENT2_H
#include "Component.h"

class AllSensorDataComponent2 : public Component
{
    public:
		AllSensorDataComponent2(MeasureMeta** measures);
        void display();
	private:
		MeasureMeta** _measures;
};

#endif