#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "../general.h"
#include "FooterComponent.h"
#include "application.h"

// http://www.barth-dev.de/online/rgb565-color-picker/

#define VIEW_NORMAL_COLOR 0xEF5D
#define VIEW_CURRENT_COLOR 0x041F

FooterComponent::FooterComponent()
{
}

void FooterComponent::display()
{
	_display->fillRect(x, y, width, height, ILI9341_BLACK);
	drawViewBar();
}

Action FooterComponent::handleEvent(Action action)
{
	//if (action != Action_SwitchToNextView)
	//	return Action_None;

	drawViewBar();
	return Action_None;
}

void FooterComponent::drawViewBar()
{
	uint8_t padding = 3;
	uint16_t start = (this->width - (parentContainer->viewCount * padding)) / 2;
	uint8_t h = this->height - (padding * 2);

	for (int i = 0; i < parentContainer->viewCount; i++)
		_display->fillRect(
			x + start + (i*(h + padding)),
			y + padding,
			h,
			h,
			i == parentContainer->currentView ? VIEW_CURRENT_COLOR : VIEW_NORMAL_COLOR);
}