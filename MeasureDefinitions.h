#ifndef _MEASUREDEFINITIONS_H
#define _MEASUREDEFINITIONS_H

#include "DataCollection.h"
#include "Sensors\AnalogDataCollector.h"
#include "Sensors\Bme280DataCollector.h"

Adafruit_BME280 bme;

TemperatureDataCollector tempDataCollector(&bme);
MeasureMeta temperatureMeasure = MeasureMeta(
	1,
	BoundariesMeasureCheck(10.0, 30.0),
	BoundariesMeasureCheck(0.0, 40.0),
	&tempDataCollector);

HumidityDataCollector humidityDataCollector(&bme);
MeasureMeta humidityMeasure = MeasureMeta(2, &humidityDataCollector);

PressureDataCollector pressureDataCollector(&bme);
MeasureMeta pressureMeasure = MeasureMeta(3, &pressureDataCollector);

AnalogDataCollector mq2GasSensor(D3);
MeasureMeta mq2Measure = MeasureMeta(
	4,
	BoundariesMeasureCheck(0, 100),
	BoundariesMeasureCheck(0, 1000),
	&mq2GasSensor);


MeasureMeta* measures[4];

#endif