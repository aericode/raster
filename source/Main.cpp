#include <iostream>
#include <vector>
#include "Command.h"
#include "JsonReader.h"
#include "Pixel.h"
#include "Canvas.h"
#include "FileBuffer.h"
#include "vec3.h"

typedef vec3 Color;
using namespace std;


void drawCommand(Command command, Canvas canvas,FileBuffer& fileBuffer){
	Color color  = command.color;
	string shape = command.shape;


	if(shape == "line"){

		Pixel start = command.position.at(0);
		Pixel end = command.position.at(1);

		canvas.drawLine(start,end, fileBuffer, color);
	}else if(shape == "circle"){

		Pixel center = command.position.at(0);
		int radius   = command.spec;

		canvas.drawCircle(center, radius, fileBuffer, color);
	}else if(shape == "polyline"){

		canvas.drawPolyline(command.position, fileBuffer, color);
	}else if(shape == "rectangle"){
		Pixel p1 = command.position.at(0);
		Pixel p2 = command.position.at(1);

		canvas.drawRectangle(p1, p2, fileBuffer, color);
	}else if(shape == "diamond"){
		Pixel p1 = command.position.at(0);
		Pixel p2 = command.position.at(1);

		canvas.drawDiamond(p1, p2, fileBuffer, color);
	}else if(shape == "isoTriangle"){
		Pixel p1 = command.position.at(0);
		Pixel p2 = command.position.at(1);

		canvas.drawIsoTriangle(p1, p2, fileBuffer, color);
	}else if(shape == "recTriangle"){
		Pixel p1 = command.position.at(0);
		Pixel p2 = command.position.at(1);

		canvas.drawRecTriangle(p1, p2, fileBuffer, color);
	}else{
		cout << "comando \"" << shape << "\" desconhecido" << endl;
	}
}

void drawCommandList(vector<Command> commandList, Canvas canvas,FileBuffer& fileBuffer){
	for (int i = 0; i < commandList.size(); ++i){
		drawCommand(commandList[i],canvas,fileBuffer);
	}

}

int main(){
	JsonReader jsonReader("JSON/default.json");
	Canvas canvas = jsonReader.readCanvas();
	FileBuffer fileBuffer = jsonReader.readFileBuffer();
	vector<Command> commands = jsonReader.readCommands();

	drawCommandList(commands, canvas, fileBuffer);
	//canvas.drawLine(80,80,100,100, fileBuffer);
	//canvas.drawRectangle(80,80,200,100, fileBuffer);
	//canvas.drawDiamond(80,80,100,100, fileBuffer);
	//canvas.drawCircle(Pixel(50,50), 10, fileBuffer);

	//canvas.drawIsoTriangle(Pixel(20,20),Pixel(50,50), fileBuffer);
	//canvas.drawRecTriangle(Pixel(120,120),Pixel(150,50), fileBuffer);

	fileBuffer.plotFile();
}