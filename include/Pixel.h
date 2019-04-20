#ifndef PIXELH
#define PIXELH
#define DEFAULT_COLOR Color(0,0,0)

#include "vec3.h"

typedef vec3 Color;

class Pixel{
public:
	Pixel();
	Pixel(int, int, Color = DEFAULT_COLOR );

	int x;
	int y;
	Color color;
};

#endif