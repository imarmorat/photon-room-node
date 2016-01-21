#ifndef _ALARM_H
#define _ALARM_H

class Alarm
{
public:
	Alarm(int buzzerPin, Adafruit_ILI9341 * display);
	void Init(MeasureMeta** measures);
	MeasureZone CheckForAlerts();
	void TriggerAlarm();
	void DisableAlarm();
	void DisplayAlerts();
	bool IsTriggered();
	int GetLevelCount(MeasureZone level);

private:
	int _buzzerPin;
	Adafruit_ILI9341 * _display;
	MeasureMeta ** _measures;
	bool _isOn = false;
};

#endif