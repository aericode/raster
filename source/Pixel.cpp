#include "Pixel.h"
#include "vec3.h"

typedef vec3 Color;

Pixel::Pixel(){}

Pixel::Pixel(int x,int y, Color color){
	this->x = x;
	this->y = y;
	this->color = color;
}