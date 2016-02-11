#ifndef _MQSERIESDATACOLLECTOR_H
#define _MQSERIESDATACOLLECTOR_H

#include "application.h"
#include "AnalogDataCollector.h"

class MqSeriesDataCollector : public AnalogDataCollector
{
public:
	explicit MqSeriesDataCollector(int8_t analogPin) : AnalogDataCollector(analogPin) {};
	void setCurve(float pointAx, float pointAy, float pointBx, float pointBy);
	void setParams(float resistanceLoad, float vIn);
	void Init();
protected:
	virtual float Transform(float value);
	float _aConstant;
	float _bConstant;
	float _resistanceLoad; // value of the resistance used on the board
	float _vIn; // voltage applied to the sensor
	float _roCalibrated;
	bool _debug = false;
};


#endif