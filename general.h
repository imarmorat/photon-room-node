#ifndef _GENERAL_H
#define _GENERAL_H

#define PLATFORM_ID 6
#include "application.h"

#define TEMPERATURE_MEASURE_ID	0
#define HUMIDITY_MEASURE_ID	1
#define PRESSURE_MEASURE_ID	2
#define MQ2_MEASURE_ID	3
#define MEASURE_COUNT 4

enum Action {
	Action_None = 0,
	Action_SwitchToNextView = 1,
	Action_RefreshView = 3,

	Event_StartAlarmRequested = 31,
	Event_StopAlarmRequested = 32,
	Event_AlarmTriggered = 35,
	Event_AlarmStopped = 34,

	//
	Event_MeasureCollectionStarted = 10,
	Event_MeasureCollectionCompleted = 11,

	//
	// buttons
	Event_Button1Pressed = 20,
	Event_Button2Pressed = 21
};

enum BoardInput : int8_t {
	BoardInput_Button1 = D3, 
	BoardInput_Button2 = D5 
};

enum MeasureZone
{
	MeasureZone_Normal = 0,
	MeasureZone_Warning = 1,
	MeasureZone_Critical = 2
};

struct MeasureCheck
{
	virtual bool Test(float value) = 0;
	virtual void debug() {};
};

struct NoMeasureCheck : MeasureCheck
{
	bool Test(float value) { return false; }
};

struct BoundariesMeasureCheck : MeasureCheck
{
	float Min;
	float Max;
	bool Test(float value) { return value >= Min && value <= Max; }
	void debug()
	{
		Particle.publish("debug", String::format("%f - %f", Min, Max));
	}

	BoundariesMeasureCheck(float min, float max) : Min(min), Max(max) {}
};



#endif