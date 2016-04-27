#include "player.h"
#include <Windows.h>

Player::Player(){
	type = "player";
	//cooldown = 5;
	//lastCooldown = 0;
	setFrame(0);
	// KeydownEvent KeypressedEvent
	keyboard.on(new KeypressedEvent(VK_UP, [this]()-> bool { this->moveUp(); this->setFrame(0); return true; }));
	keyboard.on(new KeypressedEvent(VK_DOWN, [this]()-> bool { this->moveDown(); this->setFrame(0); return true; }));
	keyboard.on(new KeypressedEvent(VK_LEFT, [this]()-> bool { this->moveLeft(); this->setFrame(1); return true; }));
	keyboard.on(new KeypressedEvent(VK_RIGHT, [this]()-> bool { this->moveRight(); this->setFrame(1); return true; }));
	keyboard.on(new KeypressedEvent(VK_SHIFT, [this]()-> bool {this->setFrame(-1); this->keyboard.clear();  return true; }));
}

void Player::iteration() {

	control();
}

void Player::control() {
	keyboard.process();
}

bool Player::moveLeft() {
	if (collide("wall",x-1,y)) return false;
	x -= 1;
	return true;
}

bool Player::moveRight() {
	if (collide("wall",x+1,y)) return false;
	x += 1;
	return true;
}

bool Player::moveUp() {
	if (collide("wall",x,y-1)) return false;
	y -= 1;
	return true;
}

bool Player::moveDown() {
	if (collide("wall",x,y+1)) return false;
	y += 1;
	return true;
}

bool Player::collide(string type) {
	bool contact = false;
	void_unit_func func = [&contact, &type, this](Unit& unit) mutable {
		if (unit.getType() != type) return;
		contact = placeMeeting(unit);
	};
	group->foreach(func);
	return contact;
}

bool Player::collide(string type, int x, int y) {
	bool contact = false;
	void_unit_func func = [x,y,&contact, &type, this](Unit& unit) mutable {
		if (unit.getType() != type) return;
		if (placeMeeting(unit, x, y)) contact = true;
	};
	group->foreach(func);
	return contact;
}
