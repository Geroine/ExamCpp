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
