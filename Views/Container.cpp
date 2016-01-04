#include "../Adafruit_ILI9341/Adafruit_ILI9341.h"
#include "../general.h"
#include "Component.h"
#include "Container.h"

void Container::init(Adafruit_ILI9341 * display)
{
	_display = display;

	if (_header != NULL)
	{
		_header->init(display, 0, 0, 20, 320);
		_header->display();
	}

	if (_footer != NULL)
	{
		_footer->init(display, 0, 240 - 16, 16, 320);
		_footer->display();
	}

	for (uint8_t i = 0; i < viewCount; i++)
	{
		_views[i]->init(_display, 0, _header->height + 1, 240 - (_header->height + _footer->height), 320);
	}
	_views[0]->display();
}

void Container::setHeader(Component* header) { _header = header; _header->parentContainer = this; }

void Container::setFooter(Component* footer) { _footer = footer; _footer->parentContainer = this; }

void Container::addView(Component* view)
{
	viewCount++;
	Component** newList = (Component**)malloc(sizeof(Component*) * viewCount);
	
	for(uint8_t i = 0; i<viewCount-1; i++)
		newList[i] = _views[i];

	newList[viewCount-1] = view;
	_views = newList;

	view->parentContainer = this;
}

Action Container::handleEvent(Action action)
{
	noInterrupts();

	// propagate the action down to each component
	Action ah = _header->handleEvent(action);
	Action af = _footer->handleEvent(action);
	Action av = _views[currentView]->handleEvent(action);	

	if (ah == Action_None && af == Action_None && av == Action_None)
	{
		// action was not handled by neither the header, the footer or the current view
		// we therefore resort to default behaviour
		
		switch (action)
		{
			case Action_None: break;
			case Event_Button1Pressed: 
			case Action_SwitchToNextView:
				switchView(); 
				break;
		}
	}

	interrupts();
	
	return Action_None;
}

void Container::refresh()
{
	_views[currentView]->display();
}

void Container::switchView()
{
	currentView++;
	if (currentView >= viewCount)
		currentView = 0;

	_views[currentView]->display();
}