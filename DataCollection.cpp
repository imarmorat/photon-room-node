#include "DataCollection.h"
#include <malloc.h>
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
	for (int i = 0; i < _size; i++)
	{
		_collectors[i]->Collect();
	}
}


