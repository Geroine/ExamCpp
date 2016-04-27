#include "processor.h"
#include <list>
#include <windows.h>
using namespace std;
Processor::Processor(int fps) {
	this->fps = fps;
}
void Processor::push(Process & proc) {
	processes.push_back(&proc);
}

bool Processor::erase(Process & proc) {
	auto iter = processes.begin();
	while (iter != processes.end()) {
		if (&proc == *iter) {
			processes.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}

void Processor::clear() {
	processes.clear();
}

int Processor::getSize() {
	return processes.size();
}

bool Processor::process(){
	int start = time(0),
		end,
		diff;

	if (processes.size() == 0) return false;
	list<list<Process*>::iterator> toRemove;
	auto iter = processes.begin();
	while (iter != processes.end()) {
		if (!(*iter)->iterate()) toRemove.push_back(iter);
		iter++;
	}

	auto riter = toRemove.begin();
	while (riter != toRemove.end()) {
		processes.erase(*riter);
		riter++;
	}

	end = time(0);
	diff = end - start;
	if (diff < 1000 / fps)
		Sleep(1000 / fps - diff);

	return true;
}

list<Process*>::iterator Processor::begin() {
	return processes.begin();
}

list<Process*>::iterator Processor::end() {
	return processes.end();
}
