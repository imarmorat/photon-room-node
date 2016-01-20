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

	//
	// User (button) or Software (levels are now within normal range) cancel the alarm
	Event_StopAlarmRequested = 2,

	//
	// levels are out of range triggering the alarms
	Event_AlarmTriggered = 5,

	//
	// The alarm is now cancelled
	Event_AlarmStopped = 4,

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
};

struct NoMeasureCheck : MeasureCheck
{
	virtual bool Test(float value) { return true; }
};

struct BoundariesMeasureCheck : MeasureCheck
{
	float Min;
	float Max;
	virtual bool Test(float value) { return value >= Min && value <= Max; }

	BoundariesMeasureCheck(float min, float max) : Min(min), Max(max) {}
};



#endif