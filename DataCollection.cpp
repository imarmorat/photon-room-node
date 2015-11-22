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
		_collectors[i]->Init();
	}

	Timer t = Timer(500, &OnTimerCollect);
}

void DataCollectorManager::OnTimerCollect()
{

}

void DataCollectorManager::AddCollector(IDataCollector * collector)
{
	IDataCollector ** newlist = (IDataCollector**) malloc((_size + 1)*sizeof(IDataCollector*));
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
		_collectors[i]->Collect();
	}

	digitalWrite(_collectionIndicatorPin, LOW);
}


