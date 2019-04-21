#ifndef COMMANDH
#define COMMANDH
#define DEFAULT_COLOR Color(0,0,0)

#include <vector>
#include <string>
#include "Pixel.h"
#include "vec3.h"

using namespace std;
typedef vec3 Color;

class Command{
public:
	string shape;
	vector<Pixel> position;
	Color color;
	int spec;

	Command();
	Command(string, vector<Pixel>, Color = DEFAULT_COLOR);

	void addPosition(int, int);
	void addPosition(Pixel);
};


#endif