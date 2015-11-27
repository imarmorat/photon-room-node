#include "application.h"
#include "..\Adafruit_BME280\Adafruit_BME280.h"
#include "Bme280DataCollector.h"

Bme280DataCollector::Bme280DataCollector(Adafruit_BME280 * bme) : _bme()
{
}

void Bme280DataCollector::Init()
{
	Wire.begin();

	if (!_bme->begin())
	{
		Particle.publish("event", "bme not working");
		while (1);
	}

	_currentValue = Collect();
}

float Bme280DataCollector::Collect()
{
	return 0;
}

/*
	TEMPERATURE
*/

float TemperatureDataCollector::Collect()
{
	_currentValue = _bme->readTemperature();
	return _currentValue;
}

/*
	HUMIDITY
*/

float HumidityDataCollector::Collect()
{
	_currentValue = _bme->readHumidity();
	return _currentValue;
}

/*
	PRESSURE
*/

float PressureDataCollector::Collect()
{
	_currentValue = _bme->readPressure() / 100.0F;
	return _currentValue;
}



