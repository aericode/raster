#ifndef JSONREADERH
#define JSONREADERH
#define DEFAULT_COLOR Color(0,0,0)

#include "json.hpp"
#include <fstream>
#include <string>
#include <vector>

#include "Canvas.h"
#include "Command.h"

typedef vec3 Color;
using json::JSON;
using namespace std;

class JsonReader{
private:
	JSON loadedFile;
	string stringFromFile(string);
public:
	JsonReader();
	JsonReader(string);
	void loadFile(string);

	Canvas readCanvas();
	FileBuffer readFileBuffer();
	vector<Command> readCommands();
};

JsonReader::JsonReader(){}

JsonReader::JsonReader(string fileName){
	loadFile(fileName);
}

string JsonReader::stringFromFile(string fileName)
{
    //pega o arquivo e transforma em uma string pronta para ser convertida em objeto
    string aux;
    string userInput;
    ifstream infile;
    infile.open (fileName);
        while(!infile.eof()){
            getline(infile,aux);
            userInput += aux;
        }
    infile.close();

    return userInput;
}

void JsonReader::loadFile(string fileName){
    JSON obj;
    string userInput = stringFromFile(fileName);
    obj = JSON::Load(userInput);
    loadedFile = obj;
}

Canvas JsonReader::readCanvas(){
	if (loadedFile["Canvas"].IsNull()){
        cout<<"no instructions for Canvas in JSON file"<<endl;
        return Canvas();
    }else{

        int x = loadedFile["Canvas"]["x"].ToInt();
        int y = loadedFile["Canvas"]["y"].ToInt();

        return Canvas(x,y);
    }
}

FileBuffer JsonReader::readFileBuffer(){
	if (loadedFile["FileBuffer"].IsNull()){
        cout<<"no instructions for FileBuffer in JSON file"<<endl;
        return FileBuffer();
    }else{

        int x = loadedFile["FileBuffer"]["x"].ToInt();
        int y = loadedFile["FileBuffer"]["y"].ToInt();

        if( loadedFile["FileBuffer"]["file"].IsNull() ){
        	return FileBuffer(x,y);
        }else{
        	string location = loadedFile["FileBuffer"]["file"].ToString();
        	return FileBuffer(x,y,location);
        }
        
    }
}

vector<Command> JsonReader::readCommands(){
	if (loadedFile["Commands"].IsNull()){
        cout<<"no instructions for Commands in JSON file"<<endl;
        return vector<Command>();
    }else{

    	vector<Command> commandList;

    	int num_primitives = loadedFile["Commands"].length();
    	int num_coordinates;

    	int xCoord;
    	int yCoord;


    	for(int i = 0; i < num_primitives; i++){

    		Command nextCommand;
			num_coordinates = loadedFile["Commands"][i]["coordinates"].length();

			for(int j = 0; j < num_coordinates;j++){
				xCoord = loadedFile["Commands"][i]["coordinates"][j][0].ToInt();
				yCoord = loadedFile["Commands"][i]["coordinates"][j][1].ToInt();
				nextCommand.addPosition(xCoord,yCoord);
			}

			//Color
			if(loadedFile["Commands"][i]["color"].IsNull()){
				nextCommand.color = DEFAULT_COLOR;
			}else{
				nextCommand.color[0] = loadedFile["Commands"][i]["color"][0].ToInt();
				nextCommand.color[1] = loadedFile["Commands"][i]["color"][1].ToInt();
				nextCommand.color[2] = loadedFile["Commands"][i]["color"][2].ToInt();
			}

			//shape to draw
			nextCommand.shape = loadedFile["Commands"][i]["shape"].ToString();


			//Radius, height, general specification
			if( !loadedFile["Commands"][i]["spec"].IsNull() ){
				nextCommand.spec = loadedFile["Commands"][i]["spec"].ToInt();
			}

			commandList.push_back(nextCommand);
        }
        return commandList;
    }
}

#endif