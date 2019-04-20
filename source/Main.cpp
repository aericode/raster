#include <iostream>
#include "Pixel.h"
#include "vec3.h"

typedef vec3 Color;
using namespace std;


int main(){
	Pixel pixel(30,0);
	cout << pixel.x << endl;
}