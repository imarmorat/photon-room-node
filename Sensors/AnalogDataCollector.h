#ifndef _ANALOGDATACOLLECTOR_H
#define _ANALOGDATACOLLECTOR_H

#include "application.h"
#include "DataCollection.h"

class AnalogDataCollector : public IDataCollector
{
public:
	AnalogDataCollector(int8_t analogPin);
	void Init();
	float Collect();

private:
	int _analogPin;
	//void(*_onMinReached)(float);
	//void (*_onMaxReached)(float);
};

#endif