#ifndef __HEADERCOMPONENT_H_
#define __HEADERCOMPONENT_H_

#include "Component.h"
#include "Container.h"

class HeaderComponent : public Component
{
public:
	HeaderComponent();
	void display();
	uint16_t x, y, height, width;
	Container * parentContainer;

};

#endif
