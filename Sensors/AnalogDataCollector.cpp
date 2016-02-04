#include "AnalogDataCollector.h"

AnalogDataCollector::AnalogDataCollector(int8_t analogPin)
{
	_analogPin = analogPin;
}

void AnalogDataCollector::Init()
{
	pinMode(_analogPin, INPUT);
}

float AnalogDataCollector::Collect()
{
	return Collect(true);
}

float AnalogDataCollector::Collect(bool doTransform)
{
	float val = analogRead(_analogPin);
	
	if (doTransform)
		val = Transform(val);

	return val;
}

//
// by default, no transformation, this will be overriden if necessary
float AnalogDataCollector::Transform(float input)
{
	return input;
}
