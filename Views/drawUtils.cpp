#include "../Adafruit_mfGFX/Adafruit_mfGFX.h"
#include "../Adafruit_ILI9341/Adafruit_ILI9341.h"
#include "math.h"
#include "../general.h"
//#include "drawUtils.h"

#define PI 3.14159265359

enum AngleLocation
{
	AngleLocation_BottomLeft = 0,
	AngleLocation_BottomRight = 1,
	AngleLocation_TopLeft = 2,
	AngleLocation_TopRight =3,
	AngleLocation_Unknown = -1
};

void xLine(Adafruit_ILI9341 * _display, int x1, int x2, int y, int16_t colour)
{
	if (colour == -1)
		return;

	while (x1 <= x2) _display->drawPixel(x1++, y, colour);
}

void yLine(Adafruit_ILI9341 * _display, int x, int y1, int y2, int16_t colour)
{
	if (colour == -1)
		return;

	while (y1 <= y2) _display->drawPixel(x, y1++, colour);
}

static uint8_t getAlpha(int color) { return (color & 0xff000000) >> 24; }
static uint8_t getRed(int color) { return (color & 0x00ff0000) >> 16; }
static uint8_t getBlue(int color) { return (color & 0x0000ff00) >> 8; }
static uint8_t getGreen(int color) { return (color & 0x000000ff); }

uint16_t convertRGB888toRGB565(unsigned int color, unsigned int background)
{
	// color is ARGB
	//
	// remove alpha
	uint8_t alpha = getAlpha(color);
	alpha = 0xff;
	float diff = 1.0 - alpha / 255.0;

	uint8_t red = (getRed(color) * (1 - diff)) + getRed(background) * diff;
	uint8_t blue = (getBlue(color) * (1 - diff)) + getBlue(background) * diff;
	uint8_t green = (getGreen(color) * (1 - diff)) + getGreen(background) * diff;

	return (((31 * (red + 4)) / 255) << 11) | (((63 * (green + 2)) / 255) << 5) | ((31 * (blue + 4)) / 255);
}

uint16_t convertRGB888toRGB565(int color)
{
	return convertRGB888toRGB565(color, 0);
}

void drawBitmap(Adafruit_ILI9341* display, int x, int y, int height, int width, Icon * icon, uint16_t bgColor)
{
	for (int i = 0; i < height - (icon->offsetBottomX + icon->offsetTopX); i++)
		for (int j = 0; j < width - (icon->offsetBottomY + icon->offsetTopY); j++)
			display->drawPixel(
				x + j + icon->offsetTopY, 
				y + i + icon->offsetTopX, 
				convertRGB888toRGB565(icon->data[i * (width - icon->offsetBottomY - icon->offsetTopY) + j], bgColor));
}

void drawBitmap(Adafruit_ILI9341* display, int x, int y, int height, int width, Icon * icon)
{
	drawBitmap(display, x, y, height, width, icon, 0);
}

//
// http://stackoverflow.com/questions/27755514/circle-with-thickness-drawing-algorithm
//
void CircleProgressBar_draw(Adafruit_ILI9341 * _display,  int xc, int yc, int inner, int outer, int16_t backgroundColor, int16_t foregroundColor, float angle)
{
	int xo = outer;
	int xi = inner;
	int y = 0;
	int erro = 1 - xo;
	int erri = 1 - xi;

	while (xo >= y) {

		//
		// BOTTOM LEFT CORNER - WORKS
		//
		if (angle > PI && angle <= 3 * PI / 2)
		{
			// do background
			//xLine(xc - xo, xc - xi, yc + y,  colour);
			//yLine(_display,xc - y,  yc + xi, yc + xo, colour);

			// do foreground
			int xbound = xc - y*tan(angle);
			int ybound = yc + y / tan(angle);

			if ( xbound <= (xc - xo) && xbound <= (xc - xi))
				xLine(_display, xc - xo, xc - xi, yc + y, foregroundColor);

			if (xbound > xc - xi) 
				xLine(_display, xc - xo, xc - xi, yc + y, backgroundColor);

			if (xbound >= (xc - xo) && xbound <= (xc - xi))
			{
				xLine(_display, xc - xo, xbound, yc + y, backgroundColor);
				xLine(_display, xbound, xc - xi, yc + y, foregroundColor);
			}

			if (ybound <= (yc + xo) && ybound <= (yc + xi))
				yLine(_display,xc - y, yc + xi, yc + xo, foregroundColor);

			if (ybound > yc + xo)
				yLine(_display, xc - y, yc + xi, yc + xo, backgroundColor);

			if (ybound <= (yc + xo) && ybound >= (yc + xi))
			{
				yLine(_display, xc - y, yc + xi, ybound, backgroundColor);
				yLine(_display, xc - y, ybound, yc + xo, foregroundColor);
			}
		}
		else
		{
			// do foreground directly
			xLine(_display,xc - xo, xc - xi, yc + y, angle > 3 * PI / 2 ? foregroundColor : backgroundColor);
			yLine(_display,xc - y, yc + xi, yc + xo, angle > 3 * PI / 2 ? foregroundColor : backgroundColor);
		}


		//
		// BOTTOM RIGHT CORNER - WORKS
		//
		if (angle > PI / 2 && angle <= PI)
		{
			// do background
			//xLine(_display,xc + xi, xc + xo, yc + y,  ILI9341_BLUE);
			//yLine(_display,xc + y,  yc + xi, yc + xo, ILI9341_BLUE);

			// do foreground
			int xbound = xc - y*tan(angle);
			int ybound = yc - y / tan(angle); 

			if (xbound <= (xc + xi) && xbound <= (xc + xo))
				xLine(_display,xc + xi, xc + xo, yc + y, foregroundColor);

			if (xbound > xc + xo)
				xLine(_display, xc + xi, xc + xo, yc + y, backgroundColor);

			if (xbound >= (xc + xi) && xbound <= (xc + xo))
			{
				xLine(_display, xc + xi, xbound, yc + y, backgroundColor);
				xLine(_display, xbound, xc + xo, yc + y, foregroundColor);
			}
			
			if (ybound >= (yc + xo) && ybound >= (yc + xi))
				yLine(_display,xc + y, yc + xi, yc + xo, foregroundColor);

			if (ybound < yc + xi)
				yLine(_display, xc + y, yc + xi, yc + xo, backgroundColor);

			if (ybound <= (yc + xo) && ybound >= (yc + xi))
			{
				yLine(_display, xc + y, ybound, yc + xo, backgroundColor);
				yLine(_display, xc + y, yc + xi, ybound, foregroundColor);
			}
		}
		else
		{
			// do foreground directly
			xLine(_display,xc + xi, xc + xo, yc + y, angle > PI / 2 ? foregroundColor : backgroundColor);
			yLine(_display,xc + y, yc + xi, yc + xo, angle > PI / 2 ? foregroundColor : backgroundColor);
		}


		//
		// TOP LEFT CORNER
		//
		if (angle > 3 * PI / 2 && angle <= 2 * PI)
		{
			// do background
			//xLine(_display,xc - xo, xc - xi, yc - y,  backgroundColor);
			//yLine(_display,xc - y,  yc - xo, yc - xi, ILI9341_GREEN);

			// do foreground
			int xbound = xc + y*tan(angle);
			int ybound = yc + y / tan(angle);

			if (xbound >= (xc - xi) && xbound >= (xc - xo))
				xLine(_display,xc - xo, xc - xi, yc - y, foregroundColor);

			if (xbound < xc - xo)
				xLine(_display, xc - xo, xc - xi, yc - y, backgroundColor);

			if (xbound >= (xc - xo) && xbound <= (xc - xi))
			{
				xLine(_display, xbound, xc - xi, yc - y, backgroundColor);
				xLine(_display, xc - xo, xbound, yc - y, foregroundColor);
			}

			if (ybound <= (yc - xo) && ybound <= (yc - xi))
				yLine(_display,xc - y, yc - xo, yc - xi, foregroundColor);

			if (ybound > yc - xi)
				yLine(_display, xc - y, yc - xo, yc - xi, backgroundColor);

			if (ybound >= (yc - xo) && ybound <= (yc - xi))
			{
				yLine(_display, xc - y, yc - xo, ybound, backgroundColor);
				yLine(_display, xc - y, ybound, yc - xi, foregroundColor);
			}
		}
		else
		{
			// do foreground directly
			xLine(_display,xc - xo, xc - xi, yc - y, angle > 3 * PI / 2 ? foregroundColor : backgroundColor);
			yLine(_display,xc - y, yc - xo, yc - xi, angle > 3 * PI / 2 ? foregroundColor : backgroundColor);
		}
		
		//
		// TOP RIGHT CORNER
		//
		if (angle > 0 && angle <= PI / 2)
		{
			// do background
			//xLine(_display,xc + xi, xc + xo, yc - y,  backgroundColor);
			//yLine(_display,xc + y,  yc - xo, yc - xi, backgroundColor);

			// do foreground
			int xbound = xc + y*tan(angle);
			int ybound = yc - y / tan(angle);
			
			if (xbound >= (xc + xi) && xbound >= (xc + xo))
				xLine(_display,xc + xi, xc + xo, yc - y, foregroundColor);

			if (xbound < xc + xi)
				xLine(_display, xc + xi, xc + xo, yc - y, backgroundColor);

			if (xbound >= (xc + xi) && xbound <= (xc + xo))
			{
				xLine(_display, xbound, xc + xo, yc - y, backgroundColor);
				xLine(_display, xc + xi, xbound, yc - y, foregroundColor);
			}

			if (ybound >= (yc - xo) && ybound >= (yc - xi))
				yLine(_display,xc + y, yc - xo, yc - xi, foregroundColor);

			if (ybound < yc - xo)
				yLine(_display, xc + y, yc - xo, yc - xi, backgroundColor);

			if (ybound >= (yc - xo) && ybound <= (yc - xi))
			{
				yLine(_display, xc + y, ybound, yc - xi, backgroundColor);
				yLine(_display, xc + y, yc - xo, ybound, foregroundColor);
			}
		}
		else
		{
			// do foreground directly
			xLine(_display,xc + xi, xc + xo, yc - y, angle > PI / 2 ? foregroundColor : backgroundColor);
			yLine(_display,xc + y, yc - xo, yc - xi, angle > PI / 2 ? foregroundColor : backgroundColor);
		}


		y++;

		if (erro < 0) {
			erro += 2 * y + 1;
		}
		else {
			xo--;
			erro += 2 * (y - xo + 1);
		}

		if (y > inner) {
			xi = y;
		}
		else {
			if (erri < 0) {
				erri += 2 * y + 1;
			}
			else {
				xi--;
				erri += 2 * (y - xi + 1);
			}
		}
	}
}

AngleLocation GetAngleLocation(float angle)
{
	if (angle > PI / 2 && angle <= PI) return AngleLocation_BottomRight;
	if (angle > 0 && angle <= PI / 2) return AngleLocation_TopRight;
	if (angle > PI && angle <= 3 * PI / 2) return AngleLocation_BottomLeft;
	if (angle > 3 * PI / 2 && angle <= 2 * PI) return AngleLocation_TopLeft;

	return AngleLocation_Unknown;
}

//void CircleProgressBar_draw2(Adafruit_ILI9341 * _display, int xc, int yc, int inner, int outer, int16_t backgroundColor, int16_t foregroundColor, float angle1, float angle2)
//{
//	int xo = outer;
//	int xi = inner;
//	int y = 0;
//	int erro = 1 - xo;
//	int erri = 1 - xi;
//
//	AngleLocation angle1Location = GetAngleLocation(angle1);
//	AngleLocation angle2Location = GetAngleLocation(angle2);
//	
//	while (xo >= y) {
//
//		//
//		// BOTTOM LEFT CORNER - WORKS
//		//
//		if (angle1Location == AngleLocation_BottomLeft || angle2Location == AngleLocation_BottomLeft)
//		{
//			// do foreground
//			int xbound = xc - y*tan(angle);
//			int ybound = yc + y / tan(angle);
//
//			if (xbound <= (xc - xo) && xbound <= (xc - xi))
//				xLine(_display, xc - xo, xc - xi, yc + y, foregroundColor);
//
//			if (xbound > xc - xi)
//				xLine(_display, xc - xo, xc - xi, yc + y, backgroundColor);
//
//			if (xbound >= (xc - xo) && xbound <= (xc - xi))
//			{
//				xLine(_display, xc - xo, xbound, yc + y, backgroundColor);
//				xLine(_display, xbound, xc - xi, yc + y, foregroundColor);
//			}
//
//			if (ybound <= (yc + xo) && ybound <= (yc + xi))
//				yLine(_display, xc - y, yc + xi, yc + xo, foregroundColor);
//
//			if (ybound > yc + xo)
//				yLine(_display, xc - y, yc + xi, yc + xo, backgroundColor);
//
//			if (ybound <= (yc + xo) && ybound >= (yc + xi))
//			{
//				yLine(_display, xc - y, yc + xi, ybound, backgroundColor);
//				yLine(_display, xc - y, ybound, yc + xo, foregroundColor);
//			}
//		}
//		else
//		{
//			// do foreground directly
//			xLine(_display, xc - xo, xc - xi, yc + y, angle > 3 * PI / 2 ? foregroundColor : backgroundColor);
//			yLine(_display, xc - y, yc + xi, yc + xo, angle > 3 * PI / 2 ? foregroundColor : backgroundColor);
//		}
//
//
//		//
//		// BOTTOM RIGHT CORNER - WORKS
//		//
//		if (angle > PI / 2 && angle <= PI)
//		{
//			// do background
//			//xLine(_display,xc + xi, xc + xo, yc + y,  ILI9341_BLUE);
//			//yLine(_display,xc + y,  yc + xi, yc + xo, ILI9341_BLUE);
//
//			// do foreground
//			int xbound = xc - y*tan(angle);
//			int ybound = yc - y / tan(angle);
//
//			if (xbound <= (xc + xi) && xbound <= (xc + xo))
//				xLine(_display, xc + xi, xc + xo, yc + y, foregroundColor);
//
//			if (xbound > xc + xo)
//				xLine(_display, xc + xi, xc + xo, yc + y, backgroundColor);
//
//			if (xbound >= (xc + xi) && xbound <= (xc + xo))
//			{
//				xLine(_display, xc + xi, xbound, yc + y, backgroundColor);
//				xLine(_display, xbound, xc + xo, yc + y, foregroundColor);
//			}
//
//			if (ybound >= (yc + xo) && ybound >= (yc + xi))
//				yLine(_display, xc + y, yc + xi, yc + xo, foregroundColor);
//
//			if (ybound < yc + xi)
//				yLine(_display, xc + y, yc + xi, yc + xo, backgroundColor);
//
//			if (ybound <= (yc + xo) && ybound >= (yc + xi))
//			{
//				yLine(_display, xc + y, ybound, yc + xo, backgroundColor);
//				yLine(_display, xc + y, yc + xi, ybound, foregroundColor);
//			}
//		}
//		else
//		{
//			// do foreground directly
//			xLine(_display, xc + xi, xc + xo, yc + y, angle > PI / 2 ? foregroundColor : backgroundColor);
//			yLine(_display, xc + y, yc + xi, yc + xo, angle > PI / 2 ? foregroundColor : backgroundColor);
//		}
//
//
//		//
//		// TOP LEFT CORNER
//		//
//		if (angle > 3 * PI / 2 && angle <= 2 * PI)
//		{
//			// do background
//			//xLine(_display,xc - xo, xc - xi, yc - y,  backgroundColor);
//			//yLine(_display,xc - y,  yc - xo, yc - xi, ILI9341_GREEN);
//
//			// do foreground
//			int xbound = xc + y*tan(angle);
//			int ybound = yc + y / tan(angle);
//
//			if (xbound >= (xc - xi) && xbound >= (xc - xo))
//				xLine(_display, xc - xo, xc - xi, yc - y, foregroundColor);
//
//			if (xbound < xc - xo)
//				xLine(_display, xc - xo, xc - xi, yc - y, backgroundColor);
//
//			if (xbound >= (xc - xo) && xbound <= (xc - xi))
//			{
//				xLine(_display, xbound, xc - xi, yc - y, backgroundColor);
//				xLine(_display, xc - xo, xbound, yc - y, foregroundColor);
//			}
//
//			if (ybound <= (yc - xo) && ybound <= (yc - xi))
//				yLine(_display, xc - y, yc - xo, yc - xi, foregroundColor);
//
//			if (ybound > yc - xi)
//				yLine(_display, xc - y, yc - xo, yc - xi, backgroundColor);
//
//			if (ybound >= (yc - xo) && ybound <= (yc - xi))
//			{
//				yLine(_display, xc - y, yc - xo, ybound, backgroundColor);
//				yLine(_display, xc - y, ybound, yc - xi, foregroundColor);
//			}
//		}
//		else
//		{
//			// do foreground directly
//			xLine(_display, xc - xo, xc - xi, yc - y, angle > 3 * PI / 2 ? foregroundColor : backgroundColor);
//			yLine(_display, xc - y, yc - xo, yc - xi, angle > 3 * PI / 2 ? foregroundColor : backgroundColor);
//		}
//
//		//
//		// TOP RIGHT CORNER
//		//
//		if (angle > 0 && angle <= PI / 2)
//		{
//			// do background
//			//xLine(_display,xc + xi, xc + xo, yc - y,  backgroundColor);
//			//yLine(_display,xc + y,  yc - xo, yc - xi, backgroundColor);
//
//			// do foreground
//			int xbound = xc + y*tan(angle);
//			int ybound = yc - y / tan(angle);
//
//			if (xbound >= (xc + xi) && xbound >= (xc + xo))
//				xLine(_display, xc + xi, xc + xo, yc - y, foregroundColor);
//
//			if (xbound < xc + xi)
//				xLine(_display, xc + xi, xc + xo, yc - y, backgroundColor);
//
//			if (xbound >= (xc + xi) && xbound <= (xc + xo))
//			{
//				xLine(_display, xbound, xc + xo, yc - y, backgroundColor);
//				xLine(_display, xc + xi, xbound, yc - y, foregroundColor);
//			}
//
//			if (ybound >= (yc - xo) && ybound >= (yc - xi))
//				yLine(_display, xc + y, yc - xo, yc - xi, foregroundColor);
//
//			if (ybound < yc - xo)
//				yLine(_display, xc + y, yc - xo, yc - xi, backgroundColor);
//
//			if (ybound >= (yc - xo) && ybound <= (yc - xi))
//			{
//				yLine(_display, xc + y, ybound, yc - xi, backgroundColor);
//				yLine(_display, xc + y, yc - xo, ybound, foregroundColor);
//			}
//		}
//		else
//		{
//			// do foreground directly
//			xLine(_display, xc + xi, xc + xo, yc - y, angle > PI / 2 ? foregroundColor : backgroundColor);
//			yLine(_display, xc + y, yc - xo, yc - xi, angle > PI / 2 ? foregroundColor : backgroundColor);
//		}
//
//
//		y++;
//
//		if (erro < 0) {
//			erro += 2 * y + 1;
//		}
//		else {
//			xo--;
//			erro += 2 * (y - xo + 1);
//		}
//
//		if (y > inner) {
//			xi = y;
//		}
//		else {
//			if (erri < 0) {
//				erri += 2 * y + 1;
//			}
//			else {
//				xi--;
//				erri += 2 * (y - xi + 1);
//			}
//		}
//	}
//}