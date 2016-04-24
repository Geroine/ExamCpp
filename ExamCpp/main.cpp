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
	KeydownEvent a(VK_UP, []() {cout << "Up" << endl; });
	KeydownEvent b(VK_DOWN, []() {cout << "Down" << endl; });
	KeypressedEvent c(VK_LEFT, []() {cout << "Left" << endl; });
	KeypressedEvent d(VK_RIGHT, []() {cout << "Right" << endl; });
	el.on(&b);
	el.on(&a);
	el.on(&c);
	el.on(&d);
	while (true) {
		el.process();
	}
}
