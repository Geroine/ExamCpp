#include "player.h"
#include <Windows.h>

Player::Player() 
	:Unit(Sprites().player){
	keyboard.on(new KeydownEvent(VK_UP, [this]()-> bool { this->moveUp(); this->setFrame(0); return true; }));
	keyboard.on(new KeydownEvent(VK_DOWN, [this]()-> bool { this->moveDown(); this->setFrame(2); return true; }));
	keyboard.on(new KeydownEvent(VK_LEFT, [this]()-> bool { this->moveLeft(); this->setFrame(1); return true; }));
	keyboard.on(new KeydownEvent(VK_RIGHT, [this]()-> bool { this->moveRight(); this->setFrame(3); return true; }));
	keyboard.on(new KeydownEvent(VK_SHIFT, [this]()-> bool {this->setFrame(-1); this->keyboard.clear();  return true; }));
}

void Player::iteration() {
	control();
}

void Player::control() {
	keyboard.process();
}

bool Player::moveLeft() {
	x -= 4;
	return true;
}

bool Player::moveRight() {
	x += 4;
	return true;
}

bool Player::moveUp() {
	y -= 4;
	return true;
}

bool Player::moveDown() {
	y += 4;
	return true;
}
