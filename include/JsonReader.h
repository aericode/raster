#ifndef JSONREADERH
#define JSONREADERH

#include "json.hpp"
#include <fstream>
#include <string>

#include "Canvas.h"


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

#endif