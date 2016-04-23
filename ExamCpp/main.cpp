#include <iostream>
#include "screen_object.h"
using namespace std;

void main()
{
	Symbol red('#', CC_Red, CC_Black);
	Symbol bckg(' ', CC_White, CC_Black);
	SmartScreen screen(40, 15, bckg);
	Canvas canv1(10, 10);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (j == i) canv1(j, i) = red;
		}
	}
	Subject subj1(canv1);
	Subject subj2(canv1);
	for (int i = 0; i < 10; i++) {
		subj2(0, i) = red;
	}
	subj2.setX(9);
	SubjectGroup group;
	Subject &ptsubj = group.push(subj2);
	//group.push(subj1);
	group.blitAllTo(screen);
	screen.draw();
	ptsubj.setX(11);
	group.blitAllTo(screen);
	screen.draw();
}
