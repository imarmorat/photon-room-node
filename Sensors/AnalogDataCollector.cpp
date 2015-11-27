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
	return digitalRead(_analogPin);
}

//
// option 1: each sensor class do the check and call AlarmManager if necessary
// option 2: alarmmanager does the check but need some more structure for each sensor/measure
// 
//
