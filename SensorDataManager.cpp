#include "SensorDataManager.h"

SensorDataManager::SensorDataManager(Adafruit_BME280 bme) : _bme()
{
}

void SensorDataManager::Init()
{
	Wire.begin();
 
    if (!_bme.begin())
    {
        Particle.publish("event", "bme not working");
        while (1);
    }
 
    // give an initial reading
    _temperature.min  = _temperature.max = _temperature.current = _bme.readTemperature();
    _humidity.min  = _humidity.max = _humidity.current = _bme.readHumidity();
    _pressure.min  = _pressure.max = _pressure.current = _bme.readPressure() / 100.0F;
}

void SensorDataManager::Collect()
{
    if (isUpdatingSensorData)
        return;
        
    isUpdatingSensorData = true;

    _temperature.current = _bme.readTemperature();
    delay(sensorDataFetchingDelay);
    
    _humidity.current = _bme.readHumidity();
    delay(sensorDataFetchingDelay);
    
    _pressure.current = _bme.readPressure() / 100.0F;
    delay(sensorDataFetchingDelay);

    digitalWrite(D7, LOW);
    if (_temperature.current < _temperature.min) _temperature.min = _temperature.current;
    if (_temperature.current > _temperature.max) _temperature.max = _temperature.current;
    
    if (_humidity.current < _humidity.min) _humidity.min = _humidity.current;
    if (_humidity.current > _humidity.max) _humidity.max = _humidity.current;
    
    if (_pressure.current < _pressure.min) _pressure.min = _pressure.current;
    if (_pressure.current > _pressure.max) _pressure.max = _pressure.current;

    //digitalWrite(D7, LOW);
    isUpdatingSensorData = false;
}
