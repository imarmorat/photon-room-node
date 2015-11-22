#ifndef _DATACOLLECTION_H
#define _DATACOLLECTION_H

class IDataCollector
{
public:
	virtual void Collect();
	virtual void Init();
};

class DataCollectorManager {
public:
	DataCollectorManager(int8_t collectionIndicatorPin);
	void AddCollector(IDataCollector *collector);
	void Init();
	void Collect();
	int collectionInterval;

private:
	IDataCollector ** _collectors;
	int _size;
	int8_t _collectionIndicatorPin;

	static void OnTimerCollect();
	static bool isCurrentlyCollecting;
};

#endif