#include <iostream>
#include <Windows.h>
#include "processor.h"
#include "rpg_game.h"
#include "bmp.h"
using namespace std;

void main(){
	SmartScreen screen(40,15);
	Unit bckg;
	bckg = Canvas(40, 15, Symbol(' ', CC_Black, CC_DarkBlue));
	Processor proc;
	Player player;
	UnitGroup grp;

	grp.push(bckg);
	grp.push(player);

	proc.push(grp);
	while (proc.process()) {
		grp.blitAll(screen.canvas());
		screen.draw();
	}
}