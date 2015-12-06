#ifndef _GENERAL_H
#define _GENERAL_H

#include "application.h"

enum Action { 
	Action_None = 0,
	Action_SwitchToNextView = 1,
	Action_StopAlarm = 2
};

enum BoardInput {
	BoardInput_Button1 = D6, 
	BoardInput_Button2 = D7 
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