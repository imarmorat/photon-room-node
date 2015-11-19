#ifndef _SENSORDATAMANAGER_H
#define _SENSORDATAMANAGER_H

#include "Adafruit_BME280/Adafruit_BME280.h"

struct sensor_data
{
    float current;
    float min;
    float max;
} ;

class SensorDataManager
{
    public:
        SensorDataManager(Adafruit_BME280 bme);
        void begin();
        void updateSensorData();
        sensor_data _temperature;
        sensor_data _humidity;
        sensor_data _pressure;

    private:
        bool isUpdatingSensorData = false;
        bool hasSensorData = true;
        int sensorDataFetchingDelay = 1000;
        
        Adafruit_BME280 _bme;
};

#endif