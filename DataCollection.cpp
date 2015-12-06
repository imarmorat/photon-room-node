#include "Application.h"
#include "general.h"
#include "DataCollection.h"
#include <malloc.h>

#define nbMeasures sizeof(_collectors)/sizeof(IDataCollector*)

DataCollectorManager::DataCollectorManager(int8_t collectionIndicatorPin)
{
	_collectionIndicatorPin = collectionIndicatorPin;
}

void DataCollectorManager::Init(MeasureMeta ** measures)
{
	pinMode(_collectionIndicatorPin, OUTPUT);

	_collectors = measures;

	for (int i = 0; i < nbMeasures; i ++ )
	{
		_collectors[i]->Init();
	}
}

void DataCollectorManager::Collect(void(*onMeasureCollectionDone)(MeasureMeta * measure))
{
	digitalWrite(_collectionIndicatorPin, HIGH);
	
	for (int i = 0; i < nbMeasures; i ++ )
	{
		_collectors[i]->Update();
		onMeasureCollectionDone(_collectors[i]);
	}

	digitalWrite(_collectionIndicatorPin, LOW);
}

//float DataCollectorManager::GetLatest(int measureId)
//{
//	for (int i = 0; i < nbMeasures; i ++ )
//	{
//		if (_collectors[i]->Id == measureId)
//			return _collectors[i]->latestValue;
//	}
//}


