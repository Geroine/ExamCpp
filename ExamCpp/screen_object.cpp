#include "screen_object.h"
#include "error.h"
#include <math.h>
#include <algorithm>

Subject::Subject(int w, int h, int depth):Canvas(w,h){
	this->depth = depth;
}

Subject::Subject(Canvas & canv, int depth){
	Canvas::operator=(canv);
	this->depth = depth;
	x = 0;
	y = 0;
}

Subject & Subject::operator=(Canvas & obj){
	Canvas::operator=(obj);
	return *this;
}

Subject & Subject::operator=(Subject & obj){
	if (this == &obj) return *this;
	Canvas::operator=(obj);
	x = obj.x;
	y = obj.y;
	depth = obj.depth;

	return *this;
}

void Subject::setX(int x){
	this->x = x;
}

void Subject::setY(int y){
	this->y = y;
}

void Subject::setPos(int x, int y){
	this->y = y;
	this->x = x;
}

int Subject::getX(){
	return x;
}

int Subject::getY(){
	return y;
}
void Subject::setDepth(int depth) {
	this->depth = depth;
}
int Subject::getDepth() {
	return depth;
}
// Функция сравнивает только по ширине и длинне. Доделать!
bool Subject::collide(Subject & obj){
	int diffX = obj.x - x;
	int diffY = obj.y - y;

	if (diffX == 0) return true;
	if (diffX > 0) {
		if (width > diffX) return true;
	} else {
		if (obj.width > abs(diffX)) return true;
	}

	if (diffY == 0) return true;
	if (diffY > 0) {
		if (height > diffY) return true;
	} else {
		if (obj.height > abs(diffY)) return true;
	}
	return false;
}

SubjectGroup::SubjectGroup(){
	size = 0;
}

void SubjectGroup::blitAllTo(Canvas & canv){
	Canvas* ptSubj;
	Subject subj;
	auto start = subjects.begin();
	for (int i = 0; i < size; i++) {
		subj = *(start++);
		ptSubj = &subj;
		canv.blit(*ptSubj,subj.getX(),subj.getY());
	}
}

void SubjectGroup::blitTo(Canvas & canv, int id){
	if (id < 0 || id >= size) throw Error("SubjectGroup blit: wrong id. Size = " + to_string(size) + " ; Id = " + to_string(id));
	auto start = subjects.begin();
	for (int i = 0; i < id; i++) {
		start++;
	}
	Subject subj = *start;
	Canvas* ptSubj = &subj;
	canv.blit(*ptSubj, subj.getX(), subj.getY());
}

Subject& SubjectGroup::push(Subject & subj){
	subjects.push_back(subj);
	size++;
	return *--subjects.end();
}

void SubjectGroup::clear(){
	subjects.clear();
	size = 0;
}

bool SubjectGroup::erase(int id){
	if (id < 0 || id >= size) return false;
	auto start = subjects.begin();
	for (int i = 0; i < id; i++) {
		start++;
	}
	subjects.erase(start);
	return true;
}

// Выбивает ошибку типизации. Чёрт знает!
bool SubjectGroup::erase(Subject & subj){
	auto iter = subjects.begin();
	while (iter != subjects.end()) {
		if (&(*iter) == &subj) {
			subjects.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}

Subject & SubjectGroup::operator[](int id){
	auto iter = subjects.begin();
	for (int i = 0; i < id; i++, iter++);
	return *iter;
}


SmartScreen::SmartScreen(int w, int h):Screen(w,h) {}
SmartScreen::SmartScreen(int w, int h, Symbol bckg): Screen(w,h,bckg){};

void SmartScreen::blit(Subject & obj, int dx, int dy, int dWidth, int dHeight){
	Canvas* canv = &obj;
	Screen::blit(*canv, obj.getX(), obj.getY(), dx, dy, dWidth, dHeight);
}

void SmartScreen::blit(Subject & obj){
	Canvas* canv = &obj;
	Screen::blit(*canv, obj.getX(), obj.getY());
}

void SmartScreen::blit(Canvas & obj, int x, int y){
	Screen::blit(obj, x, y);
}

void SmartScreen::blit(Canvas & obj, int sx, int sy, int dx, int dy, int dWidth, int dHeight){
	Screen::blit(obj, sx, sy, dx, dy, dWidth, dHeight);
}
