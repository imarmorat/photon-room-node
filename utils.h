#ifndef __GFX_UTILS_
#define __GFX_UTILS_

#include "application.h"

//uint8_t getAlpha(int color) { return (color & 0xff000000) >> 24; }
//uint8_t getRed(int color) { return (color & 0x00ff0000) >> 16; }
//uint8_t getBlue(int color) { return (color & 0x0000ff00) >> 8; }
//uint8_t getGreen(int color) { return (color & 0x000000ff); }
//
//uint16_t convertRGB888toRGB565(int color, int background)
//{
//	// color is ARGB
//	//
//	// remove alpha
//	uint8_t alpha = getAlpha(color);
//	alpha = 0xff;
//	float diff = 1.0 - alpha / 255.0;
//
//	uint8_t red = (getRed(color) * (1 - diff)) + getRed(background) * diff;
//	uint8_t blue = (getBlue(color) * (1 - diff)) + getBlue(background) * diff;
//	uint8_t green = (getGreen(color) * (1 - diff)) + getGreen(background) * diff;
//
//	return (((31 * (red + 4)) / 255) << 11) | (((63 * (green + 2)) / 255) << 5) | ((31 * (blue + 4)) / 255);
//}

#endif