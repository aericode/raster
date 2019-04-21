#include <iostream>
#include "Pixel.h"
#include "Canvas.h"
#include "FileBuffer.h"
#include "vec3.h"

typedef vec3 Color;
using namespace std;


int main(){
	Canvas canvas(400,200);
	FileBuffer fileBuffer(400,200);

	canvas.drawLine(80,80,100,100, fileBuffer);
	canvas.drawSquare(80,80,100,100, fileBuffer);
	canvas.drawCircle(Pixel(50,50), 10, fileBuffer);

	fileBuffer.plotFile();
}