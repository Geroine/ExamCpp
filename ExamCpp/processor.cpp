#include "processor.h"
#include <list>
using namespace std;
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
	return true;
}

list<Process*>::iterator Processor::begin() {
	return processes.begin();
}

list<Process*>::iterator Processor::end() {
	return processes.end();
}
