#include <vector>
#include "Canvas.h"
#include "Pixel.h"
#include "FileBuffer.h"
#include "vec3.h"

typedef vec3 Color;

Canvas::Canvas(){}

Canvas::Canvas(int xSize, int ySize){	

	this->xSize = xSize;
	this->ySize = ySize;
}

void Canvas::drawLine(int x1, int y1, int x2, int y2, FileBuffer& fileBuffer, Color color){
	Pixel starter(x1,y1);
	Pixel final(x2,y2);

	drawLine(starter, final, fileBuffer, color);
}

void Canvas::drawLine(Pixel starter, Pixel final, FileBuffer& fileBuffer, Color color){

    //inicial
    int x;
    int y;

    //final
    int xf;
    int yf;

    //deltas
    int dx;
    int dy;

    //módulo dos deltas
    int dxAbs;
    int dyAbs;


    //intervalos de erro
    int px;
    int py;

    //calculando delta
    dx = final.x - starter.x;
    dy = final.y - starter.y;

    //módulos de delta
    dxAbs = abs(dx);
    dyAbs = abs(dy);

    //intervalos de erro
    px = 2 * dyAbs - dxAbs;
    py = 2 * dxAbs - dyAbs;

    // The line is X-axis dominant
    if (dyAbs <= dxAbs) {

        
        if (dx >= 0) {
        	//esquerda para direita
        	x  = starter.x;
        	y  = starter.y;

        	xf = final.x;
        } else { 
        	//trocar e direita para esquerda
            x  = final.x;
        	y  = final.y;

        	xf = starter.x;
        }

        fileBuffer.colorPixel(Pixel(x,y), color);


        for (int i = 0; x < xf; i++) {
            x = x + 1;

            // Octantes
            if (px < 0) {
                px = px + 2 * dyAbs;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y = y + 1;
                } else {
                    y = y - 1;
                }
                px = px + 2 * (dyAbs - dxAbs);
            }

            fileBuffer.colorPixel(Pixel(x,y), color);
        }

    } else { 

        
        if (dy >= 0) {
        	// baixo - cima
            x  = starter.x;
        	y  = starter.y;

        	yf = final.y;
        } else { 
        	// cima - baixo
            x  = final.x;
        	y  = final.y;

        	yf = starter.y;
        }

        fileBuffer.colorPixel(Pixel(x,y), color);

        for (int i = 0; y < yf; i++) {
            y = y + 1;

            //Octantes
            if (py <= 0) {
                py = py + 2 * dxAbs;
            } else {
                if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) {
                    x = x + 1;
                } else {
                    x = x - 1;
                }
                py = py + 2 * (dxAbs - dyAbs);
            }

            fileBuffer.colorPixel(Pixel(x,y), color);
        }
    }
}


void Canvas::drawCircle(int x, int y, int r, FileBuffer& fileBuffer, Color color){
	drawCircle(Pixel(x,y), r, fileBuffer, color);
}

//adaptando o modelo desse site
//https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
void Canvas::drawCircle(Pixel pixel, int r, FileBuffer& fileBuffer, Color color) {

	int x_center = pixel.x;
	int y_center = pixel.y;

    int x = r, y = 0;

    
    fileBuffer.colorPixel(Pixel ( x + x_center, y + y_center), color);
      

    if (r > 0) 
    { 
    	fileBuffer.colorPixel(Pixel ( x_center, y_center - r), color);
    	fileBuffer.colorPixel(Pixel ( x_center - r, y_center), color);

    	fileBuffer.colorPixel(Pixel ( x + x_center,-y + y_center), color);
    	fileBuffer.colorPixel(Pixel ( y + x_center, x + y_center), color);
    	fileBuffer.colorPixel(Pixel (-y + x_center, x + y_center), color);
    }


    int P = 1 - r; 
    while (x > y) 
    {  
        y++; 
          

        if (P <= 0){ 
            P = P + 2*y + 1; 
        }else{ 
            x--; 
            P = P + 2*y - 2*x + 1; 
        } 
          
        if (x < y){break;}
          


        fileBuffer.colorPixel(Pixel ( x + x_center, y + y_center), color);
        fileBuffer.colorPixel(Pixel (-x + x_center, y + y_center), color);
        fileBuffer.colorPixel(Pixel ( x + x_center,-y + y_center), color);
        fileBuffer.colorPixel(Pixel (-x + x_center,-y + y_center), color);
          

        if (x != y) 
        { 
        	fileBuffer.colorPixel(Pixel ( y + x_center, x + y_center), color);
        	fileBuffer.colorPixel(Pixel (-y + x_center, x + y_center), color);
        	fileBuffer.colorPixel(Pixel ( y + x_center,-x + y_center), color);
        	fileBuffer.colorPixel(Pixel (-y + x_center,-x + y_center), color);
        } 
    } 


}

void Canvas::drawPolyline(vector<Pixel> points, FileBuffer& fileBuffer, Color color){
	for(int i = 0; i < points.size() - 1; i++)
		drawLine(points[i],points[i+1], fileBuffer, color);
}

void Canvas::drawRectangle(int x1, int y1, int x2, int y2, FileBuffer& fileBuffer, Color color){
	Pixel starter(x1,y1);
	Pixel final(x2,y2);

	drawRectangle(starter, final, fileBuffer, color);
}

void Canvas::drawRectangle(Pixel p1, Pixel p2, FileBuffer& fileBuffer, Color color){
	vector<Pixel> vertexes;
	vertexes.reserve(5);

	Pixel v1 = Pixel (p1.x, p1.y);
	Pixel v2 = Pixel (p2.x, p1.y);
	Pixel v3 = Pixel (p2.x, p2.y);
	Pixel v4 = Pixel (p1.x, p2.y);

	vertexes.push_back(v1);
	vertexes.push_back(v2);
	vertexes.push_back(v3);
	vertexes.push_back(v4);
	vertexes.push_back(v1);	
	

	drawPolyline(vertexes,fileBuffer,color);
}

void Canvas::drawDiamond(int x1, int y1, int x2, int y2, FileBuffer& fileBuffer, Color color){
	Pixel starter(x1,y1);
	Pixel final(x2,y2);

	drawDiamond(starter, final, fileBuffer, color);
}

void Canvas::drawDiamond(Pixel p1, Pixel p2, FileBuffer& fileBuffer, Color color){
	vector<Pixel> vertexes;
	vertexes.reserve(5);

	int midHeight = (p1.y + p2.y)/2;
	int midWidth  = (p1.x + p2.x)/2;


	Pixel v1 = Pixel (midWidth, p1.y);
	Pixel v2 = Pixel (p2.x, midHeight);
	Pixel v3 = Pixel (midWidth, p2.y);
	Pixel v4 = Pixel (p1.x, midHeight);

	vertexes.push_back(v1);
	vertexes.push_back(v2);
	vertexes.push_back(v3);
	vertexes.push_back(v4);
	vertexes.push_back(v1);	
	

	drawPolyline(vertexes,fileBuffer,color);
}


	
void Canvas::drawIsoTriangle(Pixel p1, Pixel p2, FileBuffer& fileBuffer, Color color){
	vector<Pixel> vertexes;
	vertexes.reserve(4);

	int midWidth  = (p1.x + p2.x)/2;


	Pixel v1 = Pixel (p1.x, p1.y);
	Pixel v2 = Pixel (midWidth, p2.y);
	Pixel v3 = Pixel (p2.x, p1.y);

	vertexes.push_back(v1);
	vertexes.push_back(v2);
	vertexes.push_back(v3);
	vertexes.push_back(v1);	
	

	drawPolyline(vertexes,fileBuffer,color);
}


void Canvas::drawRecTriangle(Pixel p1, Pixel p2, FileBuffer& fileBuffer, Color color){
	vector<Pixel> vertexes;
	vertexes.reserve(4);

	Pixel v1 = Pixel (p1.x, p1.y);
	Pixel v2 = Pixel (p2.x, p2.y);
	Pixel v3 = Pixel (p2.x, p1.y);

	vertexes.push_back(v1);
	vertexes.push_back(v2);
	vertexes.push_back(v3);
	vertexes.push_back(v1);	
	

	drawPolyline(vertexes,fileBuffer,color);
}