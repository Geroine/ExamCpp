#include <iostream>
#include <Windows.h>
#include <corecrt_wstring.h>
#include "processor.h"
#include "rpg_game.h"
#include "bmp.h"
#include "sprite_tool.h"

using namespace std;

void game(){
	SmartScreen screen(40, 25);
	Unit bckg;
	bckg = Canvas(40, 25, Symbol(' ', CC_Black, CC_Black));
	Processor proc;
	BMP pic("img/spr3.bmp", UP_MIRROR);
	pic.setMask(Pixel(250, 0, 250));

	SpriteTool sprites(pic.canvas());
	sprites.snapAll(4, 4);

	Player player;
	player.addFrame(sprites.canvas(1));
	player.addFrame(sprites.canvas(0));
	Wall wall(sprites.canvas(), 12, 5);
	//Wall wall2(wl.canvas(Pixel(250, 0, 250)), 5, 10);
	UnitGroup grp;

	grp.push(bckg);
	grp.push(player);
	grp.push(wall);
	//grp.push(wall2);

	proc.push(grp);
	while (proc.process()) {
		int xx = player.getX();
		grp.blitAll(screen.canvas());
		screen.draw();
	}
}

void main() {
	//try {
		game();
	//} catch (Error e) {
	//	string mess = e.strwhat();
	//	wstring name(mess.begin(),mess.end());
	//	const wchar_t* wmess = name.c_str();
	//	MessageBox(NULL, wmess, L"Îרטבךא ןנמדנאללû", MB_OK);
	//}

}