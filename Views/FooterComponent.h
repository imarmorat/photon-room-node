#ifndef __FOOTERCOMPONENT_H_
#define __FOOTERCOMPONENT_H_

#include "Component.h"
#include "Container.h"

class FooterComponent : public Component
{
public:
	//uint16_t x, y, height, width;
	//Container * parentContainer;

	FooterComponent();
	void display();
	Action handleEvent(Action event);
private:
	void drawViewBar();
};

#endif
