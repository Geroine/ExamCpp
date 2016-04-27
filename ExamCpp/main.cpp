#include <iostream>
#include <Windows.h>
#include "processor.h"
#include "rpg_game.h"
#include "bmp.h"
using namespace std;

void main(){
	SmartScreen screen(40,15);
	Unit bckg;
	bckg = Canvas(40, 15, Symbol(' ', CC_Black, CC_Black));
	Processor proc;

	BMP plr("img/player.bmp", UP_MIRROR);
	BMP wl ("img/wall.bmp", UP_MIRROR);

	Player player(plr.canvas(Pixel(250,0,250)));
	Wall wall(wl.canvas(Pixel(250, 0, 250)), 15, 5);
	Wall wall2(wl.canvas(Pixel(250, 0, 250)), 5, 10);
	UnitGroup grp;

	grp.push(bckg);
	grp.push(player);
	grp.push(wall);
	grp.push(wall2);

	proc.push(grp);
	while (proc.process()) {
		int xx = player.getX();
		grp.blitAll(screen.canvas());
		screen.draw();
	}
}