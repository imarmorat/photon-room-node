#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "general.h"
#include "DataCollection.h"
#include "Alarm.h"

//#define nbMeasures sizeof(_measures)/sizeof(MeasureMeta*)

Alarm::Alarm(int buzzerPin, Adafruit_ILI9341 * display)
{
	_display = display;
	_buzzerPin = buzzerPin;
}

void Alarm::Init(MeasureMeta ** measures)
{
	_measures = measures;
	pinMode(_buzzerPin, OUTPUT);
	digitalWrite(_buzzerPin, LOW);
}

void Alarm::CheckForAlerts()
{
	int nbCriticals = 0, nbWarnings = 0, nbNormals = 0;
	for (int i = 0; i < MEASURE_COUNT; i++)
	{
		switch (_measures[i]->latestLevel)
		{
			case MeasureZone_Critical: nbCriticals++; break;
			case MeasureZone_Warning: nbWarnings++; break;
			case MeasureZone_Normal: nbNormals++; break;
		}
	}
	
	if (nbCriticals > 0 || nbWarnings > 0)
		TriggerAlarm();
	else
		DisableAlarm();
}

void Alarm::TriggerAlarm()
{
	if (_isOn)
		return;

	_isOn = true;

	//
	// finally, display and ring the bell
	//tone(_buzzerPin, 2555, 0); // https://docs.particle.io/reference/firmware/core/#tone-
	digitalWrite(_buzzerPin, HIGH);
	DisplayAlerts();

	Particle.publish("events.alarm.status", "on");
}

void Alarm::DisableAlarm()
{
	if (!_isOn)
		return;

	//noTone(_buzzerPin);
	digitalWrite(_buzzerPin, LOW);
	_isOn = false;

	Particle.publish("events.alarm.status", "off");
}

bool Alarm::IsTriggered()
{
	return _isOn;
}

void Alarm::DisplayAlerts()
{
	// show a summary of the alerts
	_display->clearDisplay();
	_display->setCursor(0, 0);
	_display->setTextSize(3);
	_display->println("ALERT!!");

	// todo: display useful information
}