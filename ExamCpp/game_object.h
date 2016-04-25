#pragma once
#include "game_basic.h"

class Character : public GameObject{
	int hp;
	Character* focus;
public:
	Character(GameObject& obj, int hp = 100);
	Character();

	virtual void control();
	virtual bool moveUp();
	virtual bool moveDown();
	virtual bool moveLeft();
	virtual bool moveRight();
	virtual bool attack();

	virtual bool collide(GameObject& obj);
	virtual void focusAt(GameObject& obj);
	
};

class Wall : public GameObject {
public:
	virtual void collide(GameObject& obj);
};

class Background : public GameObject {

};