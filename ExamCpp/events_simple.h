#pragma once
#include <vector>
#include <string>
#include <queue>
#include <functional>
using namespace std;

typedef function<void()> cfunc;
class KeyboardEvent {
protected:
	int keycode;
	cfunc func;
public:
	KeyboardEvent();
	virtual void operator()();
};

class KeypressedEvent : public KeyboardEvent{
public:
	KeypressedEvent(int key, cfunc func);
	void operator()();
};

class KeydownEvent : public KeyboardEvent {
public:
	KeydownEvent(int key, cfunc func);
	void operator()();
};

class EventListener {
	//queue<KeyboardEvent> toProcess;
	vector<KeyboardEvent*> events;
public:
	EventListener();
	void process();
	void clear();
	void on(KeyboardEvent* ev);
	bool off(KeyboardEvent* ev);
	int getSize();
	//void emit(KeyboardEvent& type);
};

bool KB_Pressed(int Key);
bool KB_Hit(int Key);