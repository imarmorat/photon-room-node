#include "MqSeriesDataCollector.h"
#include <math.h>

void MqSeriesDataCollector::Init()
{
	// the sensor config acts as a voltage divider due to the internal resistor
	// therefore, with vOut being voltage across the R2 (here RL): 
	// vOut = vIn * R2/ (R1 + R2)
	// therefore R1 = [R2 * vIn / vOut] - R2

	// calibration
	int nbSampling = 25;
	int delayBetweenEachSample = 500;
	float r0InCleanAir = 9830; // ohms, as per spreadsheet
	float value = 0;
	for (int i = 0; i < nbSampling; i++)
	{
		float vMeasured = Collect(false) * 0.0008;
		value += _rl * (5 / vMeasured - 1); // we need raw values, so no transfo
		delay(delayBetweenEachSample);
	}
	value /= nbSampling; // back to average

	_roCalibrated =  1000 * value / r0InCleanAir;

	//Particle.publish("debug", String::format("caibration: %f %f %f", value, t, _roCalibrated));
}

void MqSeriesDataCollector::setCurve(float pointAx, float pointAy, float pointBx, float pointBy)
{
	//
	// some maths: on a log graph, a straight line is as follow: y = a * (x^b) which leads to ln(y) = ln(a) + b * ln(x)
	// on the datasheet: ppm = a * (rs/ro)^b
	// b is basically: b = [ln(y2) - ln(y1)] / [ln(x2) - ln(x1)]
	// once b is calculated, a is simply: a = [ln(y1) - b] / ln (x1)
	_bConstant = (log(pointBy) - log(pointAy)) / (log(pointBx) - log(pointAx));
	float lnA = log(pointBy) - _bConstant * log(pointBx);
	_aConstant = exp(lnA);

	//a=1085.641479 b=-3.203380
	//a=20123.587891 b=-2.665408
	Particle.publish("debug", String::format("a=%f b=%f", _aConstant, _bConstant));
}

void MqSeriesDataCollector::setLoadResistance(float load)
{
	_rl = load;
}

float MqSeriesDataCollector::Transform(float input)
{
	//
	// Robtillaart's approach
	// http://forum.arduino.cc/index.php/topic,55780.0.html
	float val = input * 0.0008; // convert into voltage

	float vcc = 5; // voltage provided to the sensor

	float rs = _rl * (vcc/val - 1); 
	float ppm = _aConstant * pow(rs/ _roCalibrated, _bConstant);

	return ppm;
}