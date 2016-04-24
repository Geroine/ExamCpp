#include "screen.h"
#include "console_graphics.h"
#include "string"
#include "error.h"

// Символ
Symbol::Symbol(char s, int c, int b){
    symbol = s;
    visible = true;
    if (c > 15) { c = 15; visible = false;};
    if (c < 0) {c = 0; visible = false;};
    if (b > 15) {b = 15; visible = false;};
    if (b < 0) {b = 0; visible = false;};
    color = c;
    background = b;
}

Symbol::Symbol(){
	symbol = ' ';
	visible = false;
	color = CC_White;
	background = CC_Black;
}

bool Symbol::operator==(const Symbol& obj){
    return compare(obj);
}
bool Symbol::operator!=(const Symbol & obj)
{
	return !compare(obj);
}
Symbol & Symbol::operator=(const Symbol & obj){
	if (this == &obj) return *this;
	color = obj.color;
	background = obj.background;
	symbol = obj.symbol;
	visible = obj.visible;
	return *this;
}
bool Symbol::compare(const Symbol& obj){
    if (symbol != obj.symbol) return false;
    if (color != obj.color) return false;
    if (background != obj.background) return false;
    //if (visible != obj.visible) return false;
    return true;
}
void Symbol::draw(int x, int y){
    SetConsCurPos(x,y);
    SetColorBgTex(background,color);
    cout << symbol;
}
ostream& operator<<(ostream& out, const Symbol& obj){
    SetColorBgTex(obj.background,obj.color);
    out << obj.symbol;
    return out;
}

// Холст (Canvas)
Canvas::Canvas(int w, int h){
    if (w < 0) w = 50;
    if (h < 0) h = 30;
    if (w > 100) w = 100;
    if (h > 50) h = 50;
    width = w;
    height = h;

    for (int i = 0; i < height; i++){
        vector<Symbol> symbs(width);
        canv.push_back(symbs);
    }
}


Symbol& Canvas::operator()(int x, int y){
	if (y >= canv.size() || y < 0) throw Error("Canvas operator(): bad 'y' argument. Taked " + 
		to_string(y) + " . And size = " + to_string(canv.size()));
	if (x >= canv[y].size() || x < 0) throw Error("Canvas operator(): bad 'x' argument. Taked " +
		to_string(y) + " . And size = " + to_string(canv[y].size()));
	return canv[y][x];
}

Canvas & Canvas::operator=(Canvas & obj){
	if (this == &obj) return *this;
	canv = obj.canv;
	width = obj.width;
	height = obj.height;
	return *this;
}

void Canvas::blit(Canvas & obj, int sx, int sy, int dx, int dy, int dWidth, int dHeight){
	if (dWidth > obj.getWidth()) dWidth = obj.getWidth();
	if (dHeight > obj.getHeight()) dHeight = obj.getHeight();
	if (dWidth < 0) dWidth = 0;
	if (dHeight < 0) dHeight = 0;

	for (int i = sy, oi = dy; i < this->getHeight() && oi < dHeight; oi++, i++) {
		for (int j = sx, oj = dx; j < this->getWidth() && oj < dWidth; oj++, j++) {
			if (sx < 0 || sy < 0 || dx < 0 || dy < 0) continue;
			if (obj(oj, oi).visible) {
				if (obj(oj, oi) != operator()(j, i)) {
					operator()(j, i) = obj(oj, oi);
				}
			}
		}
	}
}

void Canvas::blit(Canvas & obj, int sx, int sy){
	for (int i = sy, oi = 0; i < this->getHeight() && oi < obj.getHeight(); oi++, i++) {
		for (int j = sx, oj = 0; j < this->getWidth() && oj < obj.getWidth(); oj++, j++) {
			if (sx < 0 || sy < 0) continue;
			if (obj(oj, oi).visible) {
				if (obj(oj, oi) != operator()(j, i)) {
					operator()(j, i) = obj(oj, oi);
				}
			}
		}
	}
}

int Canvas::getWidth(){
	return width;
}

int Canvas::getHeight(){
	return height;
}

Screen::Screen(int w, int h) :prevFrame(w, h), frame(w, h) {
	width = w;
	height = h;
	prevFrameReady = false;
}

Screen::Screen(int w, int h, Symbol bckg){
	width = w;
	height = h;
	prevFrameReady = false;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			frame(j, i) = bckg;
		}
	}
}

void Screen::blit(Canvas & obj, int sx, int sy, int dx, int dy, int dWidth, int dHeight){
	if (dWidth > obj.getWidth()) dWidth = obj.getWidth();
	if (dHeight > obj.getHeight()) dHeight = obj.getHeight();
	if (dWidth < 0) dWidth = 0;
	if (dHeight < 0) dHeight = 0;

	for (int i = sy, oi = dy; i < frame.getHeight() && oi < dHeight; oi++, i++) {
		for (int j = sx, oj = dx; j < frame.getWidth() && oj < dWidth; oj++, j++) {
			if (sx < 0 || sy < 0 || dx < 0 || dy < 0) continue;
			if (obj(oj, oi).visible) {
				if (obj(oj, oi) != frame(j, i)) {
					frame(j, i) = obj(oj, oi);
				}
			}
		}
	}
}

void Screen::blit(Canvas & obj, int sx = 0, int sy = 0){
	for (int i = sy, oi = 0; i < frame.getHeight() && oi < obj.getHeight(); oi++, i++) {
		for (int j = sx, oj = 0; j < frame.getWidth() && oj < obj.getWidth(); oj++, j++) {
			if (obj(oj, oi).visible) {
				if (sx < 0 || sy < 0) continue;
				if (obj(oj, oi) != frame(j, i)) {
					frame(j, i) = obj(oj, oi);
				}
			}
		}
	}
}

void Screen::draw(){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Symbol &s = frame(j, i);
			Symbol &ps = prevFrame(j, i);
			if (!prevFrameReady) {
				ps = s;
				if (!s.visible) continue;
				SetConsCurPos(j, i);
				SetColorBgTex(s.background, s.color);
				cout << s.symbol;
			} else {
				if (ps == s) continue;
				SetConsCurPos(j, i);
				SetColorBgTex(s.background, s.color);
				cout << s.symbol;
				ps = s;
			}
			
		}
	}
	prevFrameReady = true;
}

int Screen::getWidth(){
	return width;
}

int Screen::getHeight(){
	return height;
}

Screen::operator Canvas&(){
	return frame;
}
