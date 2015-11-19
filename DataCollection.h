#ifndef _DATACOLLECTION_H
#define _DATACOLLECTION_H

class IDataCollector
{
public:
	virtual void Collect();
};

class DataCollectorManager {
public:
	void AddCollector(IDataCollector *collector);
	void Collect();
	int collectionInterval;

private:
	IDataCollector ** _collectors;
	int _size;
};

#endif