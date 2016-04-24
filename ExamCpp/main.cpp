#include <iostream>
#include "game.h"
#include "events_simple.h"
#include <Windows.h>
using namespace std;

void main()
{
	Symbol red('#', CC_Red, CC_Black);
	Symbol bckg(' ', CC_White, CC_Black);
	Canvas canv1(16,16);
	GameObject obj1;
	SmartScreen screen(40,15);
	for (int i = 0; i < canv1.getHeight(); i++) {
		for (int j = 0; j < canv1.getWidth(); j++) {
			canv1(j,i) = Symbol(' ', CC_Red, j+1);
		}
	}
	obj1 = canv1;
	Frame fr(5, 5, 5, 5);
	obj1.framePush(fr);
	
	screen.blit(obj1.canvas());
	obj1.setFrame(0);
	screen.blit(obj1.canvas(),37,10);
	screen.draw();

}
