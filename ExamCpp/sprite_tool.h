#pragma once
#include "game_basic.h"

class SpriteTool : public GameObject {
public:
	SpriteTool(Canvas& canv);
	void snapAll(int width, int height);
};