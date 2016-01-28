#ifndef _STATCOMPONENT_H
#define _STATCOMPONENT_H
#include "Component.h"

enum StatViewMode { Pressure, Temperature, Humidity };

class StatComponent : public Component
{
  public:
    StatViewMode Mode;
    void begin();
    void display();
private:
	float stats[24 * 4];

};

#endif