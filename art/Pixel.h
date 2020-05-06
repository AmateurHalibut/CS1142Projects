#ifndef RGB_H
#define RGB_H

typedef struct
{
	int rVal;   // Value of red
	int gVal;	// Value of green
	int bVal;	// Value of blue
	double grey;  // Greyscale value
	
	
} Pixel;


void initPixel(int red, int green, int blue);