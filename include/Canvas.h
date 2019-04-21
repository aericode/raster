#ifndef CANVASH
#define CANVASH
#define DEFAULT_COLOR Color(0,0,0)

#include <vector>
#include "Pixel.h"
#include "FileBuffer.h"
#include "vec3.h"

using namespace std;
typedef vec3 Color;

class Canvas{
public:
	int xSize;
	int ySize;

	Canvas();
	Canvas(int, int);

	void drawLine(int , int, int, int, FileBuffer&, Color = DEFAULT_COLOR);
	void drawLine(Pixel , Pixel, FileBuffer&, Color = DEFAULT_COLOR);
	void drawCircle(int, int, int, FileBuffer&, Color = DEFAULT_COLOR);
	void drawCircle(Pixel , int, FileBuffer&, Color = DEFAULT_COLOR);

	void drawPolyline(vector<Pixel>, FileBuffer&,Color = DEFAULT_COLOR);
	void drawRectangle(int , int, int, int, FileBuffer&, Color = DEFAULT_COLOR);
	void drawRectangle(Pixel , Pixel, FileBuffer&, Color = DEFAULT_COLOR);
	void drawDiamond(int , int, int, int, FileBuffer&, Color = DEFAULT_COLOR);
	void drawDiamond(Pixel , Pixel, FileBuffer&, Color = DEFAULT_COLOR);
	
	void drawIsoTriangle(Pixel , Pixel, FileBuffer&, Color = DEFAULT_COLOR);
	void drawRecTriangle(Pixel , Pixel, FileBuffer&, Color = DEFAULT_COLOR);

};


#endif