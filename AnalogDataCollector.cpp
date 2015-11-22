#include "AnalogDataCollector.h"

AnalogDataCollector::AnalogDataCollector(int8_t analogPin, float min, float max, float minAlarm, void(*onMinReached)(float), float maxAlarm, void(*onMaxReached)(float))
{
	_isAlarmEnabled = false;
	_analogPin = analogPin;
	_minAlarm = min;
	_maxAlarm = max;
	_onMinReached = onMinReached;
	_onMaxReached = onMaxReached;
}

void AnalogDataCollector::Init()
{
	pinMode(_analogPin, INPUT);
}

void AnalogDataCollector::Collect()
{
	_latestValue = digitalRead(_analogPin);

	if (_isAlarmEnabled)
	{
		if (_onMinReached != NULL && _latestValue < _minAlarm)
			_onMinReached(_latestValue);

		if (_onMaxReached != NULL && _latestValue > _maxAlarm)
			_onMaxReached(_latestValue);
	}
}

float AnalogDataCollector::GetLatest()
{
	return _latestValue;
}

void AnalogDataCollector::DisableAlarm()
{
	_isAlarmEnabled = false;
}

void AnalogDataCollector::EnabledAlarm()
{
	_isAlarmEnabled = true;
}