#pragma once
#include <string>
#include <vector>

class WritePL {
private:
	char* inputFile;
	char* outputFile;
	int id;
	std::string type;
	std::string content;
public:
	void setInputFile(char* InputFile) { this->inputFile = InputFile; }
	void setOutputFile(char* OutputFile) { this->outputFile = OutputFile; }
	void setID(int ID) { this->id = ID; }
	void setType(std::string Type) { this->type = Type; }
	void setContent(std::string Content) { this->content = Content; }
private:
	void* contents;
public:
	WritePL() {}
	void readContents(const char* filename, std::vector<unsigned char>& Buffer);
	void run();
	~WritePL() {}
};
