#include "Adafruit_SSD1306\Adafruit_SSD1306.h"
#include "general.h"
#include "DataCollection.h"
#include "Alarm.h"
#include "lib\list.h"

#define nbMeasures sizeof(_measures)/sizeof(MeasureMeta*)

Alarm::Alarm(int buzzerPin, Adafruit_SSD1306 * display)
{
	_display = display;
	_buzzerPin = buzzerPin;
}

void Alarm::Init(MeasureMeta ** measures)
{
	_measures = measures;
}

void Alarm::CheckForAlerts()
{
	int nbCriticals = 0, nbWarnings = 0;
	for (int i = 0; i < nbMeasures; i++)
	{
		switch (_measures[i]->latestLevel)
		{
			case MeasureZone_Critical: nbCriticals++; break;
			case MeasureZone_Warning: nbWarnings++; break;
		}
	}

	if (nbCriticals > 0 || nbWarnings > 0)
		TriggerAlarm();
	else
		DisableAlarm();
}

void Alarm::TriggerAlarm()
{
	_isOn = true;

	// todo: different display whether only warnings or error
	// warning are non blocking?


	//
	// finally, display and ring the bell
	tone(_buzzerPin, 2555, 0); // https://docs.particle.io/reference/firmware/core/#tone-
	DisplayAlerts();
}

void Alarm::DisableAlarm()
{
	noTone(_buzzerPin);
	_isOn = false;
}

void Alarm::DisplayAlerts()
{
	// show a summary of the alerts
}