#include <iostream>
#include "unit.h"
#include "events_simple.h"
#include <Windows.h>
using namespace std;

void main()
{
	Symbol red('#', CC_Red, CC_Black);
	Symbol bckg(' ', CC_White, CC_Black);
	Canvas canv1(16,16);
	Unit obj1;
	
	SmartScreen screen(40,15);
	for (int i = 0; i < canv1.getHeight(); i++) {
		for (int j = 0; j < canv1.getWidth(); j++) {
			canv1(j,i) = Symbol(' ', CC_Red, j+1);
		}
	}
	obj1 = canv1;
	Frame fr1(2, 5, 7, 5);
	Frame fr2(3, 8, 5, 5);
	obj1.framePush(fr1);
	obj1.framePush(fr2);
	
	UnitContainer units;
	obj1.setPos(0, 1);
	obj1.setFrame(0);
	units.push(obj1);
	obj1.setPos(6, 10);
	obj1.setFrame(1);
	units.push(obj1);
	UnitGroup grp(units);
	grp.blitAll(screen.canvas());
	screen.draw();
	

}