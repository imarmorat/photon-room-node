#ifndef _ALARM_H
#define _ALARM_H

class Alarm
{
public:
	Alarm(int buzzerPin, Adafruit_SSD1306 * display);
	void Init(MeasureMeta** measures);
	//void AddAlert(MeasureMeta * measure, MeasureZone zone);
	//bool RemoveAlert(MeasureMeta * measure);
	void CheckForAlerts();
	void TriggerAlarm();
	void DisableAlarm();
	void DisplayAlerts();

private:
	int _buzzerPin;
	Adafruit_SSD1306 * _display;
	MeasureMeta ** _measures;
	bool _isOn = false;

	//LinkedList<MeasureMeta> _measureAlerts;


};

#endif