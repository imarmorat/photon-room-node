#ifndef _DATACOLLECTION_H
#define _DATACOLLECTION_H

class IDataCollector
{
public:
	virtual float Collect();
	virtual void Init();
};

struct MeasureMeta
{
	int Id;
	bool canRaiseAlarm;
	float minWarning;
	float maxWarning;
	float minAlarm;
	float maxAlarm;
	float latestValue;
	IDataCollector * dataCollector;

	// TODO: initializer to avoid having to provide latestValue
	// TODO: find better approach for warning and alarm
};

class DataCollectorManager {
public:
	DataCollectorManager(int8_t collectionIndicatorPin);
	void AddCollector(MeasureMeta *collector);
	void Init();
	void Collect();
	float GetLatest(int measureId);
	int collectionInterval;

private:
	MeasureMeta ** _collectors;
	int _size;
	int8_t _collectionIndicatorPin;

	static void OnTimerCollect();
	static bool isCurrentlyCollecting;
};

#endif