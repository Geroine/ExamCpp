#include <iostream>
#include "screen_object.h"
#include "events_simple.h"
#include <Windows.h>
using namespace std;

void main()
{
	Symbol red('#', CC_Red, CC_Black);
	Symbol bckg(' ', CC_White, CC_Black);
	EventListener el;
	el.on(new KeydownEvent(VK_UP, []() {cout << "Up" << endl; }));
	el.on(new KeydownEvent(VK_DOWN, []() {cout << "Down" << endl; }));
	el.on(new KeypressedEvent(VK_LEFT, []() {cout << "Left" << endl; }));
	el.on(new KeypressedEvent(VK_RIGHT, []() {cout << "Right" << endl; }));
	while (true) {
		el.process();
	}
}
