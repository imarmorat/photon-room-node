#ifndef _MQSERIESDATACOLLECTOR_H
#define _MQSERIESDATACOLLECTOR_H

#include "application.h"
#include "AnalogDataCollector.h"

class MqSeriesDataCollector : public AnalogDataCollector
{
public:
	explicit MqSeriesDataCollector(int8_t analogPin) : AnalogDataCollector(analogPin) {};

protected:
	virtual float Transform(float value);
};


#endif