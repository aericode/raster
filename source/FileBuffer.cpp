#define RESET_COLOR vec3(255,255,255)
#include "FileBuffer.h"
#include "Pixel.h"
#include "vec3.h"

typedef vec3 Color;
using namespace std;

FileBuffer::FileBuffer(){}

FileBuffer::FileBuffer(int xSize,int ySize, string fileName){

	this->fileName = fileName;

	this->xSize = xSize;
	this->ySize = ySize;

	colorBuffer.resize(xSize*ySize);

	bufferReset();
}

void FileBuffer::bufferReset(){
	for(int i = 0;i < colorBuffer.size();i++){
		colorBuffer.at(i) = RESET_COLOR;
	}
}

void FileBuffer::plotFile(){
	ofstream imageFile;
	imageFile.open(fileName.c_str());

	imageFile << "P3" << endl;
	imageFile << xSize << " " << ySize << endl;
	imageFile << 255 << endl;

	for(int i = 0;i < colorBuffer.size();i++)
		imageFile << colorBuffer.at(i) << endl;

	imageFile.close();
}

bool FileBuffer::isValidPixel(Pixel pixel){
	bool validX = (pixel.x < xSize) && (pixel.x >= 0);
	bool validY = (pixel.y < ySize) && (pixel.y >= 0);

	return validX && validY;
}

void FileBuffer::colorPixel(Pixel pixel, Color color){
	if(!isValidPixel(pixel))return;
	int arrayLine = pixel.x + pixel.y*xSize;
	colorBuffer.at(arrayLine) = color;
}