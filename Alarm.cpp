#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "general.h"
#include "DataCollection.h"
#include "Views\drawUtils.h"
#include "Views\Container.h"
#include "Views\AlarmComponent.h"
#include "Alarm.h"

Alarm::Alarm(int buzzerPin, AlarmComponent * alarmComponent)
{
	_buzzerPin = buzzerPin;
	_alarmComponent = alarmComponent;
}

void Alarm::Init(MeasureMeta ** measures)
{
	_measures = measures;
	pinMode(_buzzerPin, OUTPUT);
	digitalWrite(_buzzerPin, LOW);
}

// returns the highest level of error
MeasureZone Alarm::CheckForAlerts()
{
	int nbCriticals = GetLevelCount(_measures, MeasureZone_Critical);
	int nbWarnings = GetLevelCount(_measures, MeasureZone_Warning);

	if (nbCriticals > 0)
		return MeasureZone_Critical;

	if (nbWarnings > 0)
		return MeasureZone_Warning;

	return MeasureZone_Normal;
}

int Alarm::GetLevelCount(MeasureMeta ** measures, MeasureZone level)
{
	int count = 0;
	for (int i = 0; i < MEASURE_COUNT; i++)
		if (measures[i]->latestLevel == level) 
			count++;

	return count;
}

void Alarm::TriggerAlarm(Container * container)
{
	if (_isOn)
		return;

	_isOn = true;

	//
	// finally, display and ring the bell
	//tone(_buzzerPin, 2555, 0); // https://docs.particle.io/reference/firmware/core/#tone-
	digitalWrite(_buzzerPin, HIGH);
	container->displayPopup(_alarmComponent);

	Particle.publish("events.alarm.status", "on");
}

void Alarm::DisableAlarm(Container * container)
{
	if (!_isOn)
		return;

	//noTone(_buzzerPin);
	digitalWrite(_buzzerPin, LOW);
	_isOn = false;

	container->hidePopup();

	Particle.publish("events.alarm.status", "off");
}

bool Alarm::IsTriggered()
{
	return _isOn;
}
