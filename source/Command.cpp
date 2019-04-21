#include <vector>
#include "Command.h"
#include "Pixel.h"
#include "vec3.h"

typedef vec3 Color;

Command::Command(){}

Command::Command(string shape, vector<Pixel> position, Color color){
	this->shape = shape;
	this->position = position;
	this->color = color;
}

void Command::addPosition(int posX, int posY){
	addPosition(Pixel(posX,posY));
}

void Command::addPosition(Pixel toAdd){
	position.push_back(toAdd);
}