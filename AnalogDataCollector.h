#ifndef _ANALOGDATACOLLECTOR_H
#define _ANALOGDATACOLLECTOR_H

#include "application.h"
#include "DataCollection.h"

class AnalogDataCollector : public IDataCollector
{
public:
	AnalogDataCollector(int8_t analogPin, float min, float max, float minAlarm, void(*onMinReached)(float), float maxAlarm, void(*onMaxReached)(float));
	void Init();
	void Collect();
	virtual float GetLatest();
	void EnabledAlarm();
	void DisableAlarm();

private:
	int _analogPin;
	float _expectedMin;
	float _expectedMax;
	float _latestValue;

	float _minAlarm;
	float _maxAlarm;
	void(*_onMinReached)(float);
	void (*_onMaxReached)(float);
	bool _isAlarmEnabled = false;
};

#endif
