#include <iostream>
#include "game_basic.h"
#include "events_simple.h"
#include <Windows.h>
using namespace std;

void main()
{
	Symbol red('#', CC_Red, CC_Black);
	Symbol bckg(' ', CC_White, CC_Black);
	Canvas canv1(16,16);
	GameObject obj1;
	obj1.setX(11);
	SmartScreen screen(40,15);
	for (int i = 0; i < canv1.getHeight(); i++) {
		for (int j = 0; j < canv1.getWidth(); j++) {
			canv1(j,i) = Symbol(' ', CC_Red, j+1);
		}
	}
	obj1 = canv1;
	Frame fr1(5, 5, 5, 5);
	Frame fr2(3, 8, 5, 5);
	obj1.framePush(fr1);
	obj1.framePush(fr2);
	
	screen.blit(obj1.canvas());
	obj1.setFrame(0);
	screen.blit(obj1.canvas(),30,10);
	obj1.setFrame(1);
	screen.blit(obj1.subject());
	screen.draw();

}
