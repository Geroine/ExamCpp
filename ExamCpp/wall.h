#include "unit.h"

class Wall : public Unit {
public:
	Wall();
	Wall(Canvas& sprite, int x, int y);
};