#ifndef __CONTAINER_H_
#define __CONTAINER_H_

class Component;

class Container
{
public:
	uint8_t height;
	uint8_t width;

	void init(Adafruit_ILI9341 * display);
	void refresh();
	void switchView();

	void setHeader(Component * view);
	void setFooter(Component * view);
	void addView(Component * view);

	Action handleEvent(Action action);

	uint8_t	viewCount;
	uint8_t	currentView;

private:
	Adafruit_ILI9341 * _display;
	Component* _header;
	Component* _footer;
	Component** _views;

};

#endif