#ifndef __FOOTERCOMPONENT_H_
#define __FOOTERCOMPONENT_H_

#include "Component.h"
#include "Container.h"

class FooterComponent : public Component
{
public:
	FooterComponent();
	void display();
	Action handleEvent(Action event);
private:
	void drawViewBar();
};

#endif
