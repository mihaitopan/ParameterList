#include "WritePL.h"
#include "Exceptions.h"
#include "ParameterList.h"
#include <windows.h>

void WritePL::readContents(const char* filename, std::vector<unsigned char>& Buffer) {
	FILE *p_file = NULL;
#pragma warning(suppress: 4996) // fopen is safe
	p_file = fopen(filename, "rb");
	fseek(p_file, 0, SEEK_END);
	int size = ftell(p_file);
	rewind(p_file);
	Buffer.resize(size);
	fread(Buffer.data(), 1, size, p_file);
	fclose(p_file);
}

void WritePL::run() {
	WIN32_FIND_DATA InputDataFile, ContentDataFile;
	HANDLE hInFind, hContentFind, hWriteFile;
	DWORD nBytesWriten, nBytesToWrite;
	BOOL bResult;

	ParameterList parli = ParameterList();

	// find files
	hInFind = FindFirstFile(this->inputFile, &InputDataFile);
	if (INVALID_HANDLE_VALUE != hInFind) {
		// read input file
		std::vector<unsigned char> Buffer;
		this->readContents(this->inputFile, Buffer);

		// load vector in parameter list
		parli.LoadFromBuffer(Buffer);
	}
	
	// do test operation
	if (this->type == "Int") {
		parli.Add(this->id, stoi(this->content));
	} else if (this->type == "String") {
		parli.Add(this->id, this->content);
	} else if (this->type == "ParameterList") {
		hContentFind = FindFirstFile(this->content.c_str(), &ContentDataFile);
		if (INVALID_HANDLE_VALUE == hContentFind) {
			throw FileException("no content file");
		}

		ParameterList pl = ParameterList();
		std::vector<unsigned char> OpBuffer;
		this->readContents(this->content.c_str(), OpBuffer);
		pl.LoadFromBuffer(OpBuffer);
		parli.Add(this->id, pl);
	} else if (this->type == "Buffer") {
		hContentFind = FindFirstFile(this->content.c_str(), &ContentDataFile);
		if (INVALID_HANDLE_VALUE == hContentFind) {
			throw FileException("no content file");
		}

		std::vector<unsigned char> OpBuffer;
		this->readContents(this->content.c_str(), OpBuffer);
		parli.Add(this->id, OpBuffer);
	} else {
		throw DataException("invalid data type");
	}

	FindClose(hInFind);
	// open output file
	hWriteFile = CreateFile(this->outputFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hWriteFile) {
		throw FileException("error opening output file for writing");
	}

	// get output buffer
	std::vector<unsigned char> OutBuffer;
	parli.SaveToBuffer(OutBuffer);
	nBytesToWrite = (DWORD)OutBuffer.size();

	// write output file
	bResult = WriteFile(hWriteFile, OutBuffer.data(), nBytesToWrite, &nBytesWriten, NULL);
	if (false == bResult || nBytesWriten != nBytesToWrite) {
		throw FileException("error writing output file");
	}

	CloseHandle(hWriteFile);	
}
