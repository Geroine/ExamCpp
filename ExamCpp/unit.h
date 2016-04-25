#pragma once
#include <list>
#include "game_basic.h"
using namespace std;

class Unit : public GameObject {
protected:
	int hp;
	Unit* focus;
public:
	Unit(GameObject& obj, int hp = 100);
	Unit();
	Unit& operator=(Canvas& obj);
	Unit& operator=(Subject& obj);
	Unit& operator=(GameObject& obj);
	Unit& operator=(Unit& obj);

	virtual void iteration() {  };

	virtual void control() {  };

	virtual bool moveUp() { return false; };
	virtual bool moveDown() { return false; };
	virtual bool moveLeft() { return false; };
	virtual bool moveRight() { return false; };
	virtual bool moveTo(int x, int y) { return false; };

	virtual bool attack() { return false; };

	virtual bool use() { return false; };

	virtual bool collide(GameObject& obj) { return false; };
	virtual void focusAt(GameObject& obj) {};

};

class UnitContainer{
	list<Unit> units;
public:
	void push(Unit& unit);
	// Нет проверки на ошибочный итератор, только на units.end()
	bool erase(list<Unit>::iterator &iter);
	void clear();
	list<Unit>::iterator begin();
	list<Unit>::iterator end();
};


// Почему то тут я использую указатели для хранения, а не сами объекты. Но переделывать всё уже поздно.
class UnitGroup : public Process {
	list<Unit*> units;
public:
	UnitGroup();
	UnitGroup(UnitContainer& container);
	void push(Unit& unit);
	void push(UnitContainer& container);
	bool erase(Unit& unit);
	void clear();

	// Итераторы
	list<Unit*>::iterator begin();
	list<Unit*>::iterator end();

	void iterateAll();
	void blitAll(Canvas& canv);

	void iterate();
};

class Process {
public:
	virtual void iterate() = 0;
};

class Processor {
	list<Process*> processes;
public:
	void push(Process& proc);
	bool erase(Process& proc);
	void clear();

	list<Process*>::iterator begin();
	list<Process*>::iterator end();
};
