#include "Application.h"

#include "DataCollection.h"
#include <malloc.h>


DataCollectorManager::DataCollectorManager(int8_t collectionIndicatorPin)
{
	_collectionIndicatorPin = collectionIndicatorPin;
}

void DataCollectorManager::Init()
{
	pinMode(_collectionIndicatorPin, OUTPUT);

	for (int i = 0; i < _size; i++)
	{
		_collectors[i]->dataCollector->Init();
	}

	Timer t = Timer(500, &OnTimerCollect);
}

void DataCollectorManager::OnTimerCollect()
{
	// Collect();
	// CheckAlarm();
}

void DataCollectorManager::AddCollector(MeasureMeta * collector)
{
	MeasureMeta ** newlist = (MeasureMeta**) malloc((_size + 1)*sizeof(MeasureMeta*));
	for (int i = 0; i<_size; i++) {
		newlist[i] = _collectors[i];
	}
	
	newlist[_size] = collector;
	_collectors = newlist;
	_size++;
}

void DataCollectorManager::Collect()
{
	digitalWrite(_collectionIndicatorPin, HIGH);

	for (int i = 0; i < _size; i++)
	{
		_collectors[i]->latestValue = _collectors[i]->dataCollector->Collect();
	}

	digitalWrite(_collectionIndicatorPin, LOW);
}

float DataCollectorManager::GetLatest(int measureId)
{
	for (int i = 0; i < _size; i++)
		if (_collectors[i]->Id == measureId)
			return _collectors[i]->latestValue;
}


