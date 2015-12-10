#include "application.h"
#include "..\Adafruit_BME280\Adafruit_BME280.h"
#include "Bme280DataCollector.h"

static bool _isInitialized = false;

Bme280DataCollector::Bme280DataCollector(Adafruit_BME280 * bme) : _bme(bme)
{
}

void Bme280DataCollector::Init()
{
	if (_isInitialized)
		return;

	delay(500);
	Particle.publish("event", "bme init");
	delay(500);

	bool result = _bme->begin();
	if (!_bme->begin())
	{
		Particle.publish("event", "bme not working");
		while (1) { Particle.process(); };
	}

	_isInitialized = true;
}

float Bme280DataCollector::Collect()
{
	return 0;
}

/*
	TEMPERATURE
*/
TemperatureDataCollector::TemperatureDataCollector(Adafruit_BME280 * bme) : Bme280DataCollector(bme)
{

}

float TemperatureDataCollector::Collect()
{
	_currentValue = _bme->readTemperature();
	return _currentValue;
}

/*
	HUMIDITY
*/
HumidityDataCollector::HumidityDataCollector(Adafruit_BME280 * bme) : Bme280DataCollector(bme)
{

}
float HumidityDataCollector::Collect()
{
	_currentValue = _bme->readHumidity();
	return _currentValue;
}

/*
	PRESSURE
*/
PressureDataCollector::PressureDataCollector(Adafruit_BME280 * bme) : Bme280DataCollector(bme)
{

}
float PressureDataCollector::Collect()
{
	_currentValue = _bme->readPressure() / 100.0F;
	return _currentValue;
}



