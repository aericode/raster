#include <iostream>
#include "JsonReader.h"
#include "Pixel.h"
#include "Canvas.h"
#include "FileBuffer.h"
#include "vec3.h"

typedef vec3 Color;
using namespace std;


int main(){
	JsonReader jsonReader("JSON/default.json");
	Canvas canvas = jsonReader.readCanvas();
	FileBuffer fileBuffer = jsonReader.readFileBuffer();

	canvas.drawLine(80,80,100,100, fileBuffer);
	canvas.drawRectangle(80,80,200,100, fileBuffer);
	canvas.drawDiamond(80,80,100,100, fileBuffer);
	canvas.drawCircle(Pixel(50,50), 10, fileBuffer);

	canvas.drawIsoTriangle(Pixel(20,20),Pixel(50,50), fileBuffer);
	canvas.drawRecTriangle(Pixel(120,120),Pixel(150,50), fileBuffer);

	fileBuffer.plotFile();
}