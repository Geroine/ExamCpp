#pragma once
#include "screen_object.h"
#include "events_simple.h"
#include <vector>
#include "error.h"

struct Frame {
	int x,
		y,
		height,
		width;
	Frame(int x = 0, int y = 0, int h = 0, int w = 0);
};

class GameObject: public Subject {
	bool solid;
	vector<Frame> frames;
	int frameIndex;
public:
	GameObject(int w = 0, int h = 0, int depth = 0, bool solid = false);
	GameObject(Canvas &canv, int depth = 0, bool solid = false);
	GameObject& operator=(Canvas& obj);
	GameObject& operator=(Subject& obj);
	GameObject& operator=(GameObject& obj);

	bool isSolid();
	void makeSolid();
	void unSolid();

	Frame fullFrame();
	int framesSize();
	void framePush(Frame& frame);
	void setFrame(int index);
	Frame& getFrame(int index);
	Frame& curFrame();
	int getFrameIndex();
	void blit(Canvas& obj);
	Canvas canvas();
	Symbol& operator()(int x, int y, int frame);
	Symbol& operator()(int x, int y);
};

class Fieldbox: public SubjectGroup {

};

class Processor {

};