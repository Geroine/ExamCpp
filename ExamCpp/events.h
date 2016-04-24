#pragma once
#include <queue>
#include <vector>
#include <functional>
using namespace std;


class Event {
	typedef function<void(void*)> func;
	string type;
	string argumentType;
	func functor;
public:
	Event(string type, func functor);
	//virtual void operator()();
	virtual void operator()(string type, void*);
	bool isCondition();
	string getType();
	string getArgumentType();
};

class EventListener {
	queue<Event> toProcess;
	vector<Event> events;
public:
	EventListener();
	void process();
	void clear();
	void on(Event& ev);
	void off(Event& ev);
	void emit(string type);
};

//class KeyboardEvent : public Event {
//	int key;
//public:
//	KeyboardEvent();
//	
//};
//
//class KeyDown : public KeyboardEvent {
//
//};

//bool KB_Pressed(int Key);
//bool KB_Hit(int Key);