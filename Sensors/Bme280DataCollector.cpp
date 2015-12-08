#include "application.h"
#include "..\Adafruit_BME280\Adafruit_BME280.h"
#include "Bme280DataCollector.h"

Bme280DataCollector::Bme280DataCollector(Adafruit_BME280 * bme) : _bme(bme)
{
}

void Bme280DataCollector::Init()
{
	bool result = _bme->begin();
	if (!_bme->begin())
	{
		Particle.publish("event", "bme not working");
		while (1) { Particle.process(); };
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



