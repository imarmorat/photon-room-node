#ifndef __CONTAINER_H_
#define __CONTAINER_H_

class Component;

class Container
{
public:
	int height;
	int width;

	void init(Adafruit_ILI9341 * display);
	void refresh();
	void switchView();

	void setHeader(Component * view);
	void setFooter(Component * view);
	void addView(Component * view);
	void hidePopup();
	void displayPopup(Component * component);
	Action handleEvent(Action action);
	int currentViewIdx;
	int viewCount;

private:
	Adafruit_ILI9341 * _display;
	Component* _header;
	Component* _footer;
	Component** _views;
	Component* _currentView;
};

#endif