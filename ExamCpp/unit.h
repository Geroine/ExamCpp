#pragma once
#include <list>
#include <string>
#include <functional>
#include "game_basic.h"
#include "processor.h"

using namespace std;

class UnitGroup;

class Unit : public GameObject {
protected:
	int hp;
	Unit* focus;
	UnitGroup* group;
	string type;
public:
	Unit(GameObject& obj, int hp = 100);
	Unit(GameObject& obj, UnitGroup& group, int hp = 100);
	Unit();
	Unit& operator=(Canvas& obj);
	Unit& operator=(Subject& obj);
	Unit& operator=(GameObject& obj);
	Unit& operator=(Unit& obj);

	void setGroup(UnitGroup& g);
	void exitGroup();
	UnitGroup* getGroup();
	string getType();

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
	virtual bool collide(string type) { return false; };
	virtual void focusAt(GameObject& obj) {};

};

class UnitContainer{
	list<Unit> units;
public:
	void push(Unit& unit);
	// ��� �������� �� ��������� ��������, ������ �� units.end()
	bool erase(list<Unit>::iterator &iter);
	void clear();
	list<Unit>::iterator begin();
	list<Unit>::iterator end();
};



typedef function<void(Unit&)> void_unit_func;
typedef function<bool(Unit&)> bool_unit_func;

// ������ �� ��� � ��������� ��������� ��� ��������, � �� ���� �������. �� ������������ �� ��� ������.
class UnitGroup : public Process {
	list<Unit*> units;
public:
	UnitGroup();
	UnitGroup(UnitContainer& container);
	void push(Unit& unit, bool linkGroup = true);
	void push(UnitContainer& container);
	bool erase(Unit& unit);
	void clear();

	// ���������
	list<Unit*>::iterator begin();
	list<Unit*>::iterator end();

	void iterateAll();
	void blitAll(Canvas& canv);
	// ��������� ��� ������
	void foreach(void_unit_func func);
	list<Unit*> find(bool_unit_func func);

	bool iterate();
};
