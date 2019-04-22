#ifndef FILEBUFFERH
#define FILEBUFFERH
#define DEFAULT_COLOR Color(0,0,0)
#define DEFAULT_IMGFILE "image/default.ppm"

#include <vector>
#include <fstream>
#include "vec3.h"
#include "Pixel.h"

typedef vec3 Color;
using namespace std;

class FileBuffer{
private:
	bool isValidPixel(Pixel);

public:
	int xSize;
	int ySize;
	vector<Color> colorBuffer;
	string fileName;

	FileBuffer();
	FileBuffer(int, int, string = DEFAULT_IMGFILE);

	void bufferReset();
	void plotFile();
	void colorPixel(Pixel, Color = DEFAULT_COLOR);
	Color colorAt(Pixel);
};

#endif