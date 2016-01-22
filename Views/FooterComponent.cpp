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
	// TODO: these calculations should be done in constructor

	int horizontalPadding = 10;
	int verticalPadding = 2;
	int indicatorSize = 10; // this->height - (verticalPadding * 2);

	int containerWidth = parentContainer->viewCount * indicatorSize + horizontalPadding * (parentContainer->viewCount - 1);
	int startX = x + (width - containerWidth) / 2;
	int startY = y + height / 2;

	for (int i = 0; i < parentContainer->viewCount; i++)
	{
		bool isCurrentView = (i == parentContainer->currentViewIdx);
		int ih = indicatorSize * (isCurrentView ? 1 : 0.5) / 2;
		int ix = startX + indicatorSize / 2 + i * (indicatorSize + horizontalPadding);

		if (!isCurrentView)
			// because the indicator for non current view is smaller, we clear the area
			_display->fillRect(ix - indicatorSize/2, startY - indicatorSize/2, indicatorSize, indicatorSize, ILI9341_BLACK);

		_display->fillRect(ix - ih, startY - ih, ih * 2, ih * 2, isCurrentView ? VIEW_CURRENT_COLOR : VIEW_NORMAL_COLOR);
	}
}