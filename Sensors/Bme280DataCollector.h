#ifndef _BME280DATACOLLECTOR_H
#define _BME280DATACOLLECTOR_H

#include "..\DataCollection.h"

class Bme280DataCollector : public IDataCollector
{
public:
	Bme280DataCollector(Adafruit_BME280 * bme);
	void Init();
	virtual float Collect();

protected:
	Adafruit_BME280 * _bme;
	float _currentValue;
};

class TemperatureDataCollector : public Bme280DataCollector
{
public:
	TemperatureDataCollector(Adafruit_BME280 * bme);
	float Collect();
};

class HumidityDataCollector : public Bme280DataCollector
{
public:
	HumidityDataCollector(Adafruit_BME280 * bme);
	float Collect();
};

class PressureDataCollector : public Bme280DataCollector
{
public:
	PressureDataCollector(Adafruit_BME280 * bme);
	float Collect();
};

#endif