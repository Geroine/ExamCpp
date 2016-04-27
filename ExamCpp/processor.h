#pragma once
#include <list>
#include <time.h>
using namespace std;

class Process {
public:
	virtual bool iterate() = 0;
};

class Processor {
	list<Process*> processes;
	int fps;
public:
	Processor(int fps = 1200);
	void push(Process& proc);
	bool erase(Process& proc);
	void clear();
	int getSize();
	bool process();

	list<Process*>::iterator begin();
	list<Process*>::iterator end();
};
