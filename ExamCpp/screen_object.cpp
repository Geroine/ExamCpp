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
	for (int i = 0; i < size; i++) {
		subj = subjects[i];
		ptSubj = &subj;
		canv.blit(*ptSubj,subj.getX(),subj.getY());
	}
}

void SubjectGroup::blitTo(Canvas & canv, int id){
	if (id < 0 || id >= size) throw Error("SubjectGroup blit: wrong id. Size = " + to_string(size) + " ; Id = " + to_string(id));
	Subject subj = subjects[id];
	Canvas* ptSubj = &subj;
	canv.blit(*ptSubj, subj.getX(), subj.getY());
}

Subject& SubjectGroup::push(Subject & subj){
	subjects.push_back(subj);
	size++;
	return subjects[subjects.size()-1];
}

void SubjectGroup::clear(){
	subjects.clear();
	size = 0;
}

bool SubjectGroup::erase(int id){
	if (id < 0 || id >= size) return false;
	auto iter = subjects.begin() + id;
	subjects.erase(iter);
	return true;
}

// Выбивает ошибку типизации. Чёрт знает!
bool SubjectGroup::erase(Subject & subj){
	//auto iter = find(subjects.begin(), subjects.end(), subj);
	//if (iter == subjects.end()) return false;
	//subjects.erase(iter);
	//return true;
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
