#pragma once
#include <string>
#include <vector>

class ReadPL {
private:
	char* inputFile;
	char* outputFile;
	int id;
	std::string type;
public:
	void setInputFile(char* InputFile) { this->inputFile = InputFile; }
	void setOutputFile(char* OutputFile) { this->outputFile = OutputFile; }
	void setID(int ID) { this->id = ID; }
	void setType(std::string Type) { this->type = Type; }
public:
	ReadPL() {}
	void readContents(const char* filename, std::vector<unsigned char>& Buffer);
	void run();
	~ReadPL() {}
};
