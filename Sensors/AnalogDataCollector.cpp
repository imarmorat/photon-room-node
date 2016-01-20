#include "AnalogDataCollector.h"
#include <math.h>

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

	//
	// Robtillaart's approach
	// http://forum.arduino.cc/index.php/topic,55780.0.html
	float val = analogRead(_analogPin) * 0.0008;

	float rs = 20000.0 * (5.0 - val) / val;
	float ratio = rs / 10000.0;
	float ppm = 37143 * pow(ratio, -3.178);

	return ppm;
}

//
// option 1: each sensor class do the check and call AlarmManager if necessary
// option 2: alarmmanager does the check but need some more structure for each sensor/measure
// 
//
