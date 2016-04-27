#include "sprite_tool.h"

SpriteTool::SpriteTool(Canvas & canv)
	:GameObject(canv){}

void SpriteTool::snapAll(int w, int h) {
	for (int i = 0; i < height / h; i++) {
		for (int j = 0; j < width / w; j++) {
			framePush(Frame(j*w, i*h, h, w));
		}
	}
}
