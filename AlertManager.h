#ifndef _ALERTMANAGER_H
#define _ALERTMANAGER_H

class AlertManager
{
public:
	void Setup(Adafruit_SSD1306 * display, int8_t buzzerPin);
	void DisableAlarm();
	void EnabledAlarm();

private:
	bool _isAlarmEnabled;
	Adafruit_SSD1306 * _display;
	int8_t _buzzerPin;
};

#endif
