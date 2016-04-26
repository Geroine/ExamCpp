#pragma once
#include <list>
using namespace std;

class Process {
public:
	virtual bool iterate() = 0;
};

class Processor {
	list<Process*> processes;
public:
	void push(Process& proc);
	bool erase(Process& proc);
	void clear();
	int getSize();
	bool process();

	list<Process*>::iterator begin();
	list<Process*>::iterator end();
};
