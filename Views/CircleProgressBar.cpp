#include "../Adafruit_mfGFX/Adafruit_mfGFX.h"
#include "../Adafruit_ILI9341/Adafruit_ILI9341.h"
#include "math.h"

#define PI 3.14159265359

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

//http://stackoverflow.com/questions/27755514/circle-with-thickness-drawing-algorithm
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