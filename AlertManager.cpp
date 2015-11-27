#include "Adafruit_SSD1306\Adafruit_SSD1306.h"
#include "AlertManager.h"

void AlertManager::Setup(Adafruit_SSD1306 * display, int8_t buzzerPin)
{
	_isAlarmEnabled = false;
	_display = display;
	_buzzerPin = buzzerPin;
}

void AlertManager::DisableAlarm()
{
	_isAlarmEnabled = false;
}

void AlertManager::EnabledAlarm()
{
	_isAlarmEnabled = true;
}

//typedef struct Measure
//{
//	int MetadataId;
//	float LatestValue;
//};

/*

class IAlarmMechanism
{
public:
	virtual bool Check(Measure * measure);
};

class BoundaryAlarmMechanism : public IAlarmMechanism
{
public:
	BoundaryAlarmMechanism(float alarmMin, float alarmMax);
	bool Check(Measure * measure);

private:
	float _alarmMin;
	float _alarmMax;
};

BoundaryAlarmMechanism::BoundaryAlarmMechanism(float alarmMin, float alarmMax)
{
	_alarmMax = alarmMax;
	_alarmMin = alarmMin;
}

bool BoundaryAlarmMechanism::Check(Measure * measure)
{
	return (measure->LatestValue > _alarmMin && measure->LatestValue < _alarmMax);
}
*/