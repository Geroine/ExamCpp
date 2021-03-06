#include "events_simple.h"
#include <list>
#include <vector>
#include <string>
#include <queue>
#include <windows.h>
#include <iostream>

using namespace std;



bool KB_Pressed(int Key)
{
	short keyState = GetAsyncKeyState(Key);
	return ((keyState & 0x8000) > 0);
}

bool KB_Hit(int Key)
{
	static list<int> KBHitBase;
	if (KB_Pressed(Key))
	{
		auto iter = KBHitBase.begin();
		while (iter != KBHitBase.end())
		{
			if (*iter == Key)
				return false;
			iter++;
		}
		KBHitBase.push_back(Key);
		return true;
	}
	if (KBHitBase.size() && !KB_Pressed(Key))
	{
		auto iter = KBHitBase.begin();
		while (iter != KBHitBase.end())
		{
			if (*iter == Key)
			{
				KBHitBase.erase(iter);
				break;
			}
			iter++;
		}
	}

	return false;
}

KeyboardEvent::KeyboardEvent(){
	keycode = -1;
	func = []() -> bool { return false; };
}

void KeyboardEvent::operator()(){

}

KeypressedEvent::KeypressedEvent(int key, cfunc func){
	keycode = key;
	this->func = func;
}

void KeypressedEvent::operator()(){
	if (KB_Pressed(keycode)) func();
}

KeydownEvent::KeydownEvent(int key, cfunc func){
	keycode = key;
	this->func = func;
}

void KeydownEvent::operator()(){
	if (KB_Hit(keycode)) func();
}

void EventListener::_clear() {
	auto iter = events.begin();
	while (iter != events.end()) {
		delete *iter;
		iter++;
	}
	events.clear();
}

EventListener::EventListener(){
	nextClear = false;
}

void EventListener::process(){
	if (nextClear) _clear();
	auto iter = events.begin();
	while (iter != events.end()) {
		(**iter)();
		iter++;
	}
}

void EventListener::clear(){
	nextClear = true;
}

void EventListener::on(KeyboardEvent * ev){
	events.push_back(ev);
}

bool EventListener::off(KeyboardEvent * ev){
	auto iter = events.begin();
	while (iter != events.end()) {
		if (&(*iter) == &ev) {
			delete *iter;
			events.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}

int EventListener::getSize(){
	return events.size();
}
