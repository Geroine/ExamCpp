#pragma once
#include "screen.h"
#include <list>
#include <vector>


class Subject : public Canvas {
protected:
	int x, y;
	int depth;
public:
	Subject(int w = 0, int h = 0, int depth = 0);
	Subject(Canvas &canv, int depth = 0);
	Subject& operator=(Canvas& obj);
	Subject& operator=(Subject& obj);
	void setX(int x);
	void setY(int y);
	void setPos(int x, int y);
	int getX();
	int getY();
	void setDepth(int depth);
	int getDepth();
	// Не проверен
	virtual bool collide(Subject& obj);
};

class SubjectGroup {
protected:
	list<Subject> subjects;
	int size;
public:
	SubjectGroup();
	// Не проверен
	void blitAllTo(Canvas& canv);
	void blitTo(Canvas& canv, int id);
	Subject& push(Subject& subj);
	void clear();
	bool erase(int id);
	bool erase(Subject& subj);
	Subject& operator[](int id);
};

class SmartScreen : public Screen {
public:
	SmartScreen(int w, int h);
	SmartScreen(int w, int h, Symbol bckg);
	void blit(Subject& obj, int dx, int dy, int dWidth, int dHeight);
	void blit(Subject& obj);
	void blit(Canvas& obj, int x = 0, int y = 0);
	void blit(Canvas& obj, int sx, int sy, int dx, int dy, int dWidth, int dHeight);
};