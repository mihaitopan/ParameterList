#pragma once
#include <exception>
#include <string>

class DataException : public std::exception {
private:
	std::string message;
public:
	DataException(std::string msg) : message(msg) {}
	const char* what() const override { return message.c_str(); }
};

class TypeException : public std::exception {
private:
	std::string message;
public:
	TypeException(std::string msg) : message(msg) {}
	const char* what() const override { return message.c_str(); }
};

class FileException : public std::exception {
private:
	std::string message;
public:
	FileException(std::string msg) : message(msg) {}
	const char* what() const override { return message.c_str(); }
};
