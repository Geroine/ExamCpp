#pragma once
#include "unit.h"
#include "events_simple.h"



struct MoveUnit {
	int key;
};

class Player : public Unit {
protected:
	EventListener keyboard;
	//int cooldown;
	//int lastCooldown;
public:
	Player();
	void iteration();

	void control();

	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();

	bool collide(string type);
	bool collide(string type, int x, int y);
};