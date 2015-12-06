#ifndef _DATACOLLECTION_H
#define _DATACOLLECTION_H

#include "general.h"

class IDataCollector
{
public:
	virtual float Collect();
	virtual void Init();
};

class MeasureMeta
{
public:
	int Id;
	bool canRaiseAlarm;
	float latestValue;
	MeasureZone latestLevel;

	//
	// Constructor
	MeasureMeta(int id, MeasureCheck warning, MeasureCheck error, IDataCollector * dataCollector) :
		Id(id), WarningCheck(warning), ErrorCheck(error), DataCollector(dataCollector)
	{
		canRaiseAlarm = true;
	}

	//
	// Constructor
	MeasureMeta(int id, IDataCollector * dataCollector) : Id(id), DataCollector(dataCollector)
	{
		canRaiseAlarm = true;
		WarningCheck = NoMeasureCheck();
		ErrorCheck = NoMeasureCheck();
	}

	void Init()
	{
		latestValue = -1;
		latestLevel = MeasureZone_Normal;
		DataCollector->Init();
	}

	//
	// Gets the latest value and update level
	void Update()
	{
		latestValue = DataCollector->Collect();
		latestLevel = CheckAgainstLevels();
	}

private:
	MeasureCheck WarningCheck;
	MeasureCheck ErrorCheck;
	IDataCollector * DataCollector;

	//
	// Checks the latest value against the defined zones
	MeasureZone CheckAgainstLevels()
	{
		if (ErrorCheck.Test(latestValue))
			return MeasureZone_Critical;

		if (WarningCheck.Test(latestValue))
			return MeasureZone_Warning;

		return MeasureZone_Normal;
	}
};

class DataCollectorManager {
public:
	DataCollectorManager(int8_t collectionIndicatorPin);
	//void AddCollector(MeasureMeta *collector);
	void Init(MeasureMeta ** measures);
	void Collect(void(*onMeasureCollectionDone)(MeasureMeta *measure));
	float GetLatest(int measureId);
	int collectionInterval;

private:
	MeasureMeta ** _collectors;
	//int _size;
	int8_t _collectionIndicatorPin;

	static bool isCurrentlyCollecting;
};

#endif