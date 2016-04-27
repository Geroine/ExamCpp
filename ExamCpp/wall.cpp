#include "wall.h"

Wall::Wall() {
	type = "wall";
	solid = true;
}

Wall::Wall(Canvas & sprite, int x, int y) {
	take(sprite);
	type = "wall";
	this->x = x;
	this->y = y;
	solid = true;
}
