#ifndef _MQSERIESDATACOLLECTOR_H
#define _MQSERIESDATACOLLECTOR_H

#include "application.h"
#include "AnalogDataCollector.h"

class MqSeriesDataCollector : public AnalogDataCollector
{
public:
	explicit MqSeriesDataCollector(int8_t analogPin) : AnalogDataCollector(analogPin) {};
	void setCurve(float pointAx, float pointAy, float pointBx, float pointBy);
	void setLoadResistance(float value);
	void Init();
protected:
	virtual float Transform(float value);
	float _aConstant;
	float _bConstant;
	float _rl;
	float _roCalibrated;
};


#endif