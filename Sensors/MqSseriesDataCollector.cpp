#include "MqSeriesDataCollector.h"
#include <math.h>

static float calcSensorResistanceLoad(float vInput, float vSensor, float boardResistanceLoad) 
{
	return  boardResistanceLoad * (vSensor / vInput - 1);
}

void MqSeriesDataCollector::Init()
{
	// the sensor config acts as a voltage divider due to the internal resistor
	// therefore, with vOut being voltage across the R2 (here RL): 
	// vOut = vIn * R2/ (R1 + R2)
	// therefore R1 = [R2 * vIn / vOut] - R2 = R2 * (vIn/vOut - 1)

	// calibration
	int nbSampling = 25;
	int delayBetweenEachSample = 500;
	float ratioCleanAir = 9.830; // RS/RO in clean air
	float value = 0;

	for (int i = 0; i < nbSampling; i++)
	{
		float vMeasured = Collect(false) * 0.0008;
		value += calcSensorResistanceLoad(vMeasured, _vIn, _resistanceLoad); // we need raw values, so no transfo, RL omitted
		delay(delayBetweenEachSample);
	}
	value /= nbSampling; // back to average

	_roCalibrated =  value / ratioCleanAir;

	if (_debug)
		Particle.publish("debug", String::format("caibration: %f", _roCalibrated));
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

	if (_debug)
		Particle.publish("debug", String::format("a=%f b=%f", _aConstant, _bConstant));
}

void MqSeriesDataCollector::setParams(float resistanceLoad, float vIn)
{
	_resistanceLoad = resistanceLoad;
	_vIn = vIn;
}

float MqSeriesDataCollector::Transform(float input)
{
	//
	// Robtillaart's approach
	// http://forum.arduino.cc/index.php/topic,55780.0.html
	float vMeasured = input * 0.0008; // convert into voltage
	float rs = calcSensorResistanceLoad(vMeasured, _vIn, _resistanceLoad);
	float ppm = _aConstant * pow(rs/ _roCalibrated, _bConstant);

	return ppm;
}