#pragma once
#include "unit.h"
#include "events_simple.h"

struct Sprites {
	GameObject player;
	Sprites():player(16,4) {
		char playerSprite[4][17] = {
			" BB  RR  RR  RR ",
			"RBBRBBRRRRRRRRBB",
			"RRRRBBRRRBBRRRBB",
			" RR  RR  BB  RR "
		};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 16; j++) {
				Symbol s(' ', CC_Black, CC_Black);
				if (playerSprite[i][j] == 'B') s.background = CC_Blue;
				if (playerSprite[i][j] == 'R') s.background = CC_Red;
				player(j, i) = s;
				for (int i = 0; i < 4; i++) {
					player.framePush(Frame(i * 4, 0, 4, 4));
				}
			}
		}
	};
	
} sprites;

struct MoveUnit {
	int key;
};

class Player : public Unit {
	EventListener keyboard;
public:
	Player();
	void iteration() {};

	void control();

	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();
};