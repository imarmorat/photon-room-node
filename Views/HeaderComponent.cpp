#include "Adafruit_ILI9341\Adafruit_ILI9341.h"
#include "HeaderComponent.h"
#include "application.h"

HeaderComponent::HeaderComponent()
{
	height = 20;
	width = 320;
	x = 0;
	y = 0;
}

void HeaderComponent::display()
{
	_display->fillRect(x, y, width, height, ILI9341_BLUE);
	// more to come

	// wifi signal + connection status
	// time
	// nb of errors and warning
	// data collecction indicator
}