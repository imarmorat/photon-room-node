

#ifndef _GAS32_H_
#define _GAS32_H_

const int gas32_height = 32; 
const int gas32_width = 32; 
const int gas32_offsetTopX = 0; 
const int gas32_offsetTopY = 5; 
const int gas32_offsetBottomX = 0; 
const int gas32_offsetBottomY = 5; 
const unsigned int gas32 [] = 
{
 	0x00000000,  	0x00000000,  	0x10FFFFFF,  	0xCFFFFFFF,  	0xCFFFFFFF,  	0x10FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x10FFFFFF,  	0xCFFFFFFF,  	0xBFFFFFFF,  	0x10FFFFFF,  	0x00000000,  	0x00000000, 	 
 	0x00000000,  	0x10FFFFFF,  	0xCFFFFFFF,  	0xFFFFFFFF,  	0xC0FFFFFF,  	0x20FFFFFF,  	0x00000000,  	0x50FFFFFF,  	0x9FFFFFFF,  	0xCFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xDFFFFFFF,  	0x9FFFFFFF,  	0x4FFFFFFF,  	0x00000000,  	0x20FFFFFF,  	0xC0FFFFFF,  	0xFFFFFFFF,  	0xCFFFFFFF,  	0x10FFFFFF,  	0x00000000, 	 
 	0x10FFFFFF,  	0xCFFFFFFF,  	0xFFFFFFFF,  	0x90FFFFFF,  	0x00000000,  	0x40FFFFFF,  	0xDFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xDFFFFFFF,  	0x40FFFFFF,  	0x00000000,  	0x70FFFFFF,  	0xFFFFFFFF,  	0xCFFFFFFF,  	0x10FFFFFF, 	 
 	0xC0FFFFFF,  	0xFFFFFFFF,  	0x90FFFFFF,  	0x00000000,  	0x80FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x8FFFFFFF,  	0x00000000,  	0x60FFFFFF,  	0xFFFFFFFF,  	0xBFFFFFFF, 	 
 	0xD0FFFFFF,  	0xB0FFFFFF,  	0x00000000,  	0x80FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x9FFFFFFF,  	0x00000000,  	0xB0FFFFFF,  	0xD0FFFFFF, 	 
 	0x10FFFFFF,  	0x20FFFFFF,  	0x50FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x50FFFFFF,  	0x10FFFFFF,  	0x10FFFFFF, 	 
 	0x00000000,  	0x00000000,  	0xE0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xEFFFFFFF,  	0x10FFFFFF,  	0x00000000, 	 
 	0x00000000,  	0x60FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x70FFFFFF,  	0x00000000, 	 
 	0x00000000,  	0xC0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xCFFFFFFF,  	0x00000000, 	 
 	0x00000000,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x00000000, 	 
 	0x30FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xF0FFFFFF,  	0x80FFFFFF,  	0x80FFFFFF,  	0xB0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xE0FFFFFF,  	0x80FFFFFF,  	0x70FFFFFF,  	0xC0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x40FFFFFF, 	 
 	0x40FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xF0FFFFFF,  	0x20FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x70FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xD0FFFFFF,  	0x10FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0xB0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x40FFFFFF, 	 
 	0x40FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x90FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0xD0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x30FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x40FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x40FFFFFF, 	 
 	0x40FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x80FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0xC0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x40FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x40FFFFFF, 	 
 	0x10FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xDFFFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0xD0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x40FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x80FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x20FFFFFF, 	 
 	0x00000000,  	0xD0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x9FFFFFFF,  	0x10FFFFFF,  	0x00000000,  	0x00000000,  	0x90FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xCFFFFFFF,  	0x20FFFFFF,  	0x00000000,  	0x00000000,  	0x50FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xE0FFFFFF,  	0x00000000, 	 
 	0x00000000,  	0x90FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xBFFFFFFF,  	0xDFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xBFFFFFFF,  	0xDFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xA0FFFFFF,  	0x00000000, 	 
 	0x00000000,  	0x30FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x40FFFFFF,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0xC0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xE0FFFFFF,  	0x00000000,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0xB0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xAFFFFFFF,  	0x10FFFFFF,  	0x00000000, 	 
 	0x10FFFFFF,  	0xCFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xDFFFFFFF,  	0x20FFFFFF, 	 
 	0x20FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x30FFFFFF, 	 
 	0x00000000,  	0x80FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x90FFFFFF,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0xD0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xE0FFFFFF,  	0x10FFFFFF,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0x30FFFFFF,  	0xFFFFFFFF,  	0xF0FFFFFF,  	0x50FFFFFF,  	0xD0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xF0FFFFFF,  	0x50FFFFFF,  	0xE0FFFFFF,  	0xFFFFFFFF,  	0x40FFFFFF,  	0x00000000,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0x00000000,  	0x30FFFFFF,  	0x10FFFFFF,  	0x00000000,  	0x30FFFFFF,  	0xF0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xF0FFFFFF,  	0x30FFFFFF,  	0x00000000,  	0x10FFFFFF,  	0x30FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x30FFFFFF,  	0x80FFFFFF,  	0x80FFFFFF,  	0x80FFFFFF,  	0x80FFFFFF,  	0x80FFFFFF,  	0x80FFFFFF,  	0x30FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x10FFFFFF,  	0x3FFFFFFF,  	0x3FFFFFFF,  	0x3FFFFFFF,  	0x3FFFFFFF,  	0x3FFFFFFF,  	0x3FFFFFFF,  	0x3FFFFFFF,  	0x3FFFFFFF,  	0x10FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0xE0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xDFFFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000, 	 
 	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0xC0FFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xFFFFFFFF,  	0xD0FFFFFF,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000,  	0x00000000, 	 
};


#endif