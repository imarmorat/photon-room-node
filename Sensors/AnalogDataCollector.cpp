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
	float val = Transform(analogRead(_analogPin));
	return val;
}

//
// by default, no transformation, this will be overriden if necessary
float AnalogDataCollector::Transform(float input)
{
	return input;
}
