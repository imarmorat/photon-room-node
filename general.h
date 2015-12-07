#ifndef _GENERAL_H
#define _GENERAL_H

#include "application.h"

#define TEMPERATURE_MEASURE_ID	0
#define HUMIDITY_MEASURE_ID	1
#define PRESSURE_MEASURE_ID	2
#define MEASURE_COUNT 3

enum Action { 
	Action_None = 0,
	Action_SwitchToNextView = 1,
	Action_StopAlarm = 2
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
	virtual bool Test(float value) { return true; }
};

struct NoMeasureCheck : MeasureCheck
{
	bool Test(float value) { return true; }
};

struct BoundariesMeasureCheck : MeasureCheck
{
	float Min;
	float Max;
	bool Test(float value) { return value >= Min && value <= Max; }

	BoundariesMeasureCheck(float min, float max) : Min(min), Max(max) {}
};



#endif