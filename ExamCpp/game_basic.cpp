#include "game_basic.h"

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
	if (diffx < 0) frame.width -= diffx;
	int diffy = height -(frame.y + frame.height);
	if (frame.y > height)  throw Error("GameObject framePush: bad frame");
	if (diffy < 0) frame.height -= diffy;
	frames.push_back(frame);
}

void GameObject::setFrame(int index){
	frameIndex = index;
}

Frame & GameObject::frameLink(int index){
	if (index < 0 || index >= frames.size()) throw Error("Wrong index");
	return frames[index];
}

Frame GameObject::getFrame(int index){
	if (index < 0 || index >= frames.size()) return Frame();
	return frames[index];
}


Frame GameObject::curFrame(){
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

void GameObject::addFrame(Canvas & obj) {
	int w = width;
	int h = height;
	int nw, nh;
	nw = obj.getWidth() + w;
	if (obj.getHeight() > height) nh = obj.getHeight(); else nh = h;
	Canvas canv(nw, nh);
	canv.blit(canvas(fullFrame()), 0, 0);
	canv.blit(obj, width, 0);
	take(canv);
	framePush(Frame(w, 0, obj.getWidth(), obj.getHeight()));
}

Canvas GameObject::canvas(int frameId){
	Frame frame = getFrame(frameId);
	Canvas canv(frame.width, frame.height);
	canv.blit(*this, 0, 0, frame.x, frame.y, frame.width, frame.height);
	return canv;
}

Canvas GameObject::canvas(Frame frame) {
	Canvas canv(frame.width, frame.height);
	canv.blit(*this, 0, 0, frame.x, frame.y, frame.width, frame.height);
	return canv;
}

Canvas GameObject::canvas(int x, int y, int w, int h) {
	Canvas canv(w, h);
	canv.blit(*this, 0, 0, x, y, w, h);
	return canv;
}

Canvas GameObject::canvas(){
	Frame frame = curFrame();
	Canvas canv(frame.width, frame.height);
	canv.blit(*this, 0, 0, frame.x, frame.y, frame.width, frame.height);
	return canv;
}

Subject GameObject::subject(){
	Frame frame = curFrame();
	Subject subj(frame.width, frame.height);
	subj.blit(*this, 0, 0, frame.x, frame.y, frame.width, frame.height);
	subj.setX(this->x);
	subj.setY(this->y);

	return subj;
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
bool GameObject::placeMeeting(GameObject & obj) {
	return placeMeeting(obj, x, y);
}
bool GameObject::placeMeeting(GameObject & obj, int x, int y) {
	int width = curFrame().width;
	int height = curFrame().height;
	int owidth = obj.curFrame().width;
	int oheight = obj.curFrame().height;
	int diffX = obj.x - x;
	int diffY = obj.y - y;
	int result = 0;

	if (diffX == 0) result++;
	else
		if (diffX > 0) {
			if (width > diffX) result++;
		} else {
			if (owidth > abs(diffX)) result++;
		}

	if (diffY == 0) result++;
	else
		if (diffY > 0) {
			if (height > diffY) result++;
		} else {
			if (oheight > abs(diffY)) result++;
		}
	return result == 2;
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

GameObject::GameObject(Subject & subj, int depth, bool solid)
	:Subject(subj,depth){
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

GameObject & GameObject::take(Canvas & obj) {
	operator=(obj);
	return *this;
}

GameObject & GameObject::take(Subject & obj) {
	operator=(obj);
	return *this;
}

GameObject & GameObject::take(GameObject & obj) {
	operator=(obj);
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
