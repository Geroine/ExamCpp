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
	virtual const char* what() throw(){
		return message.c_str();
	}
	string strwhat() throw() {
		return message;
	}
};