#ifndef __DRAWUTILS_H_
#define __DRAWUTILS_H_

void CircleProgressBar_draw(Adafruit_ILI9341 * _display, int xc, int yc, int inner, int outer, int16_t backgroundColor, int16_t foregroundColor, float angle);
void drawBitmap(Adafruit_ILI9341* display, int x, int y, int height, int width, const unsigned int * bitmap);
uint16_t convertRGB888toRGB565(int color, int background);
uint16_t convertRGB888toRGB565(int color); // assumes bg is black

#endif