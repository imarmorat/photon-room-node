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

protected:
	virtual float Transform(float value);

private:
	int _analogPin;
};

class AnalogPercentageDataCollector : public AnalogDataCollector
{
public:
	explicit AnalogPercentageDataCollector(uint8_t pin) : AnalogDataCollector(pin) {}

protected:
	float Transform(float value) 
	{
		float vMax = 3.3;
		float vMin = 0;
		float vInput = value * 0.0008;

		float percent = (vInput - vMin) / (vMax - vMin);

		return percent * 100.0;
	};
};

#endif
