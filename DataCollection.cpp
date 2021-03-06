#include "Application.h"
#include "general.h"
#include "DataCollection.h"
#include <malloc.h>

//#define nbMeasures sizeof(_collectors)/sizeof(MeasureMeta*)

DataCollectorManager::DataCollectorManager(int8_t collectionIndicatorPin)
{
	_collectionIndicatorPin = collectionIndicatorPin;
}

void DataCollectorManager::Init(MeasureMeta ** measures)
{
	delay(500);

	pinMode(_collectionIndicatorPin, OUTPUT);
	digitalWrite(_collectionIndicatorPin, HIGH);
	_collectors = measures;

	for (int i = 0; i < MEASURE_COUNT; i ++ )
	{	
		_collectors[i]->Init();
	}
	digitalWrite(_collectionIndicatorPin, LOW);
}

void DataCollectorManager::Collect(void(*onMeasureCollectionDone)(MeasureMeta * measure))
{
	digitalWrite(_collectionIndicatorPin, HIGH);
	
	for (int i = 0; i < MEASURE_COUNT; i++)
	{
		_collectors[i]->Update();
		onMeasureCollectionDone(_collectors[i]);
	}

	digitalWrite(_collectionIndicatorPin, LOW);
}



