#include "MqSeriesDataCollector.h"
#include <math.h>

float MqSeriesDataCollector::Transform(float input)
{
	//
	// Robtillaart's approach
	// http://forum.arduino.cc/index.php/topic,55780.0.html
	float val = input * 0.0008; // convert into voltage

	float rs = 20000.0 * (5.0 - val) / val; // 5.0 is the vInput
	float ratio = rs / 10000.0;
	float ppm = 37143 * pow(ratio, -3.178);

	return ppm;
}