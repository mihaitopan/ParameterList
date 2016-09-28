#include "ReadPL.h"
#include "Exceptions.h"
#include "ParameterList.h"
#include <windows.h>
#include <iostream>

void ReadPL::readContents(const char* filename, std::vector<unsigned char>& Buffer) {
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

void ReadPL::run() {
	WIN32_FIND_DATA InputDataFile;
	HANDLE hInFind, hWriteFile;
	DWORD nBytesWriten, nBytesToWrite;
	BOOL bResult; bool bWrite = false;

	ParameterList parli = ParameterList();

	// find files
	hInFind = FindFirstFile(this->inputFile, &InputDataFile);
	if (INVALID_HANDLE_VALUE == hInFind) {
		throw FileException("input file not found");
	}

	// read input file
	std::vector<unsigned char> Buffer;
	std::vector<unsigned char> OutBuffer;
	this->readContents(this->inputFile, Buffer);

	// load vector in parameter list
	parli.LoadFromBuffer(Buffer);

	// do test operation
	if (this->type == "Int") {
		int res;
		if (parli.Get(this->id, res) == 0) {
			std::cout << "match found: " << res << std::endl;
		} else {
			std::cout << "no matches" << std::endl;
		}
	} else if (this->type == "String") {
		std::string result;
		if (parli.Get(this->id, result) == 0) {
			std::cout << "match found: " << result << std::endl;
		} else {
			std::cout << "no matches" << std::endl;
		}
	} else if (this->type == "ParameterList") {
		ParameterList pl = ParameterList();
		if (parli.Get(this->id, pl) == 0) {
			std::cout << "match found - written in output file"<< std::endl;
			pl.SaveToBuffer(OutBuffer);
			bWrite = true;
		} else {
			std::cout << "no matches" << std::endl;
		}
	} else if (this->type == "Buffer") {
		if (parli.Get(this->id, OutBuffer) == 0) {
			std::cout << "match found - written in output file" << std::endl;
			bWrite = true;
		} else {
			std::cout << "no matches" << std::endl;
		}
	} else {
		throw DataException("invalid data type");
	}

	FindClose(hInFind);
	if (bWrite == true) {
		// open output file
		hWriteFile = CreateFile(this->outputFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hWriteFile) {
			throw FileException("error opening output file for writing");
			return;
		}

		// get output buffer
		nBytesToWrite = (DWORD)OutBuffer.size();

		// write output file
		bResult = WriteFile(hWriteFile, OutBuffer.data(), nBytesToWrite, &nBytesWriten, NULL);
		if (false == bResult || nBytesWriten != nBytesToWrite) {
			throw FileException("error writing output file");
			return;
		}

		CloseHandle(hWriteFile);
	}
}
