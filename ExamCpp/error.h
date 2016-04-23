#pragma once
#include <exception>
#include <string>
using namespace std;

class Error : public exception{
	string message;
public:
	Error(string message) {
		this->message = message;
	}
	virtual const char* what() const throw(){
		return message.c_str();
	}
};