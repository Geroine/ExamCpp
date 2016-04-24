#include "game.h"

Frame::Frame(int x, int y, int h, int w){
	this->x = x;
	this->y = y;
	height = h;
	width = w;
}

Frame GameObject::fullFrame(){
	return Frame(0,0,height,width);
}

int GameObject::framesSize(){
	return frames.size();
}

void GameObject::framePush(Frame& frame){
	int diffx = width - (frame.x + frame.width);
	if (frame.x > width)  throw Error("GameObject framePush: bad frame");
	if (diffx <= 0) frame.width -= diffx;
	int diffy = height -(frame.y + frame.height);
	if (frame.y > height)  throw Error("GameObject framePush: bad frame");
	if (diffy <= 0) frame.height -= diffy;
	frames.push_back(frame);
}

void GameObject::setFrame(int index){
	frameIndex = index;
}

Frame & GameObject::getFrame(int index){
	if (index < 0 || index >= frames.size()) throw Error("GameObject getFrame: wrong id. Size = " +
		to_string(frames.size()) + " ; Id = " + to_string(index));
	return frames[index];
}


Frame & GameObject::curFrame(){
	if (frameIndex >= frames.size() || frameIndex < 0) return fullFrame();
	return frames[frameIndex];
}

int GameObject::getFrameIndex(){
	return frameIndex;
}

void GameObject::blit(Canvas & obj){
	if (frameIndex > 0 && frameIndex < frames.size()) {
		Frame& cur = frames[frameIndex];
		Canvas::blit(obj, x, y, cur.x, cur.y, cur.width, cur.height);
		return;
	} else {
		Canvas::blit(obj, x, y);
	}
}

Canvas GameObject::canvas(){
	Canvas canv(curFrame().width, curFrame().height);
	canv.blit(*this, 0, 0);
	return canv;
}

Symbol & GameObject::operator()(int x, int y, int frame){
	int nx = x + getFrame(frame).x;
	int ny = y + getFrame(frame).y;
	return canv[ny][nx];
}

Symbol & GameObject::operator()(int x, int y) {
	int nx = x + curFrame().x;
	int ny = y + curFrame().y;
	return canv[ny][nx];
}
GameObject::GameObject(int w, int h, int depth, bool solid)
	:Subject(w, h, depth){
	this->solid = solid;
	frameIndex = -1;
}

GameObject::GameObject(Canvas & canv, int depth, bool solid)
	:Subject(canv,depth){
	this->solid = solid;
	frameIndex = -1;
}

GameObject & GameObject::operator=(Canvas & obj){
	Canvas::operator=(obj);
	return *this;
}

GameObject & GameObject::operator=(Subject & obj){
	Subject::operator=(obj);
	return *this;
}

GameObject & GameObject::operator=(GameObject & obj){
	if (this == &obj) return *this;
	Subject::operator=(obj);
	solid = obj.solid;
	frames = obj.frames;
	frameIndex = obj.frameIndex;
	return *this;
}

bool GameObject::isSolid(){
	return solid;
}

void GameObject::makeSolid(){
	solid = true;
}

void GameObject::unSolid(){
	solid = false;
}
