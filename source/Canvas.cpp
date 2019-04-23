#define WHITE Color(1,1,1)

#include <vector>
#include <bits/stdc++.h> 
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

void Canvas::floodFill(Pixel coord, FileBuffer& fileBuffer, Color newColor){
	Color oldColor = fileBuffer.colorAt(coord);
	floodFill(coord, fileBuffer, oldColor, newColor);
}

//baseado em https://www.geeksforgeeks.org/flood-fill-algorithm-implement-fill-paint/
void Canvas::floodFill(Pixel coord, FileBuffer& fileBuffer, Color oldColor, Color newColor){

	if(fileBuffer.colorAt(coord) == oldColor)
	{
		int x = coord.x;
		int y = coord.y;

		fileBuffer.colorPixel(Pixel(x,y), newColor);

		floodFill(Pixel(x + 1, y), fileBuffer, oldColor, newColor);
		floodFill(Pixel(x, y + 1), fileBuffer, oldColor, newColor);
		floodFill(Pixel(x - 1, y), fileBuffer, oldColor, newColor);
		floodFill(Pixel(x, y - 1), fileBuffer, oldColor, newColor);
	}
}

int Canvas::bezierGetPosition(int a, int b, float perc){
	int delta = b - a;
	return a + (delta * perc);
}

void Canvas::bezierCurve(Pixel p1, Pixel p2, Pixel p3, FileBuffer& fileBuffer, Color color){
	Pixel a;
	Pixel b;

	Pixel drawLocation;

	for( float i = 0 ; i < 1 ; i += 0.01 ){
		a.x = bezierGetPosition(p1.x, p2.x, i);
		a.y = bezierGetPosition(p1.y, p2.y, i);
		b.x = bezierGetPosition(p2.x, p3.x, i);
		b.y = bezierGetPosition(p2.y, p3.y, i);


		drawLocation.x = bezierGetPosition( a.x , b.x, i);
		drawLocation.y = bezierGetPosition( a.y , b.y, i);

		fileBuffer.colorPixel(drawLocation, color);
	}
}


//Implementação do xiaolin wu
//adaptado de https://www.geeksforgeeks.org/anti-aliased-line-xiaolin-wus-algorithm/
//utiliza o modelo da fonte para modificar o brilho da cor inserida

//returns fractional part of a number 
float Canvas::fPartOfNumber(float x) 
{ 
    if (x>0) return x - (int)x; 
    else return x - ((int)x + 1); 
  
} 
  
//returns 1 - fractional part of number 
float Canvas::rfPartOfNumber(float x) 
{ 
    return 1 - fPartOfNumber(x); 
} 
  
void Canvas::aaDrawPixel( int x , int y , float brightness, FileBuffer& fileBuffer, Color color) 
{ 
	Color background = WHITE;
	color.make_unit_vector();

	Color unit_result = (color * brightness) + ((1 - brightness)* background );

	unit_result*=255;

	unit_result[0] = (int)unit_result[0];
	unit_result[1] = (int)unit_result[1];
	unit_result[2] = (int)unit_result[2];

    fileBuffer.colorPixel(Pixel(x,y), unit_result);
} 
  
void Canvas::drawAALine(int x0 , int y0 , int x1 , int y1, FileBuffer& fileBuffer, Color color) 
{ 
    int steep = abs(y1 - y0) > abs(x1 - x0) ; 
  

    if (steep) 
    { 
        swap(x0 , y0); 
        swap(x1 , y1); 
    } 
    if (x0 > x1) 
    { 
        swap(x0 ,x1); 
        swap(y0 ,y1); 
    } 
  
    //compute the slope 
    float dx = x1-x0; 
    float dy = y1-y0; 
    float gradient;
    if (dx == 0.0){
        gradient = 1; 
    }else{
    	gradient = dy/dx; 
    }
  
    int xpxl1 = x0; 
    int xpxl2 = x1; 
    float intersectY = y0; 
  
    // main loop 
    if (steep) 
    { 
        int x; 
        for (x = xpxl1 ; x <=xpxl2 ; x++) 
        { 
            // pixel coverage is determined by fractional 
            // part of y co-ordinate 
            aaDrawPixel((int)intersectY, x, 
                        rfPartOfNumber(intersectY), fileBuffer, color); 
            aaDrawPixel((int)intersectY - 1, x, 
                        fPartOfNumber(intersectY), fileBuffer, color); 
            intersectY += gradient; 
        } 
    } 
    else
    { 
        int x; 
        for (x = xpxl1 ; x <=xpxl2 ; x++) 
        { 
            // pixel coverage is determined by fractional 
            // part of y co-ordinate 
            aaDrawPixel(x, (int)intersectY, 
                        rfPartOfNumber(intersectY), fileBuffer, color); 
            aaDrawPixel(x, (int)intersectY - 1, 
                          fPartOfNumber(intersectY), fileBuffer, color); 
            intersectY += gradient; 
        } 
    } 
  
} 


void Canvas::lineRepeater(Pixel starter, Pixel final, FileBuffer& fileBuffer, Color color, int thickness){

	//lineBres(starter,final);

	int dx = final.x - starter.x;
	int dy = final.y - starter.y;

	bool isVertical = false;

	if(dx == 0){
		dx = 1;//não dividir por zero
		isVertical = true;
	}

	if(dy/dx < 1 && !isVertical){
        for(int i = 0 ; i < thickness;i++){

        	Pixel   upStarter(starter.x  , starter.y + i);
        	Pixel     upFinal(final.x    , final.y   + i);

			Pixel   downStarter(starter.x, starter.y - i);
			Pixel     downFinal(final.x  , final.y   - i);


            drawLine(upStarter,upFinal, fileBuffer, color);
			drawLine(downStarter,downFinal, fileBuffer, color);

        }
    }else{
        for(int i = 0; i < thickness; i++){

        	Pixel   rightStarter(starter.x + i, starter.y);
        	Pixel     rightFinal(final.x   + i,   final.y);

			Pixel   leftStarter(starter.x - i,  starter.y);
			Pixel     leftFinal(final.x   - i,    final.y);


            drawLine(rightStarter,rightFinal, fileBuffer, color);
			drawLine(leftStarter,leftFinal, fileBuffer, color);
        }
    }
}