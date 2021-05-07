#include "Player.hpp"




Player::~Player() {

}

void Player::handleEvent(Event e) {

	if (e.key.code == Keyboard::Left) {
		if (e.type == Event::KeyPressed) {
			moveLeft = true;
		}
		else if (e.type == Event::KeyReleased) {
			moveLeft = false;
		}
	}

	if (e.key.code == Keyboard::Right) {
		if (e.type == Event::KeyPressed) {
			moveRight = true;
		}
		else if (e.type == Event::KeyReleased) {
			moveRight = false;
		}
	}
}

void Player::update(Int32 tpf) {
	if (tpf <= 0) {
		return;
	}

	sf::Vector2f pos = getPosition();

	if (moveLeft == moveRight) {
		// hareketsiz kal
		return;
	}

	float xVel = speed * (tpf / 1000.0f);

	if (moveLeft) {
		xVel *= -1;
	}

	setPosition(pos.x + xVel, pos.y);
}




