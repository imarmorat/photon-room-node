#ifndef _ALARM_H
#define _ALARM_H

class AlarmComponent;

class Alarm
{
public:
	Alarm(int buzzerPin, AlarmComponent * alarmComponent);
	void Init(MeasureMeta** measures);
	MeasureZone CheckForAlerts();
	void TriggerAlarm(Container * container);
	void DisableAlarm(Container * container);
	bool IsTriggered();
	static int GetLevelCount(MeasureMeta** measures, MeasureZone level);

private:
	int _buzzerPin;
	AlarmComponent * _alarmComponent;
	MeasureMeta ** _measures;
	bool _isOn = false;
};

#endif