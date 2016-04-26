#include "player.h"
#include <Windows.h>

Player::Player() 
	:Unit(sprites.player){
	keyboard.on(new KeypressedEvent(VK_UP, [this]()-> bool { this->moveUp(); this->setFrame(0); return true; }));
	keyboard.on(new KeypressedEvent(VK_DOWN, [this]()-> bool { this->moveDown(); this->setFrame(2); return true; }));
	keyboard.on(new KeypressedEvent(VK_LEFT, [this]()-> bool { this->moveLeft(); this->setFrame(1); return true; }));
	keyboard.on(new KeypressedEvent(VK_RIGHT, [this]()-> bool { this->moveRight(); this->setFrame(3); return true; }));
}

void Player::control() {
	keyboard.process();
}
