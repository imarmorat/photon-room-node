#ifndef _ALLSENSORDATACOMPONENT2_H
#define _ALLSENSORDATACOMPONENT2_H
#include "Component.h"

class AllSensorDataComponent2 : public Component
{
    public:
		AllSensorDataComponent2(MeasureMeta* measure);
        void display();
		Action handleEvent(Action action);
		void refresh();

	private:
		MeasureMeta* _measure;
};

#endif