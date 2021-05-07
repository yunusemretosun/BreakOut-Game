#pragma once

#include "SFML/Graphics.hpp"

#include "RectangleEntity.hpp"

using namespace sf;

class Player : public RectangleEntity {
public:
	Player(float w, float h) :
		RectangleEntity(w, h), speed(0), moveLeft(false), moveRight(false)
	{
	};
	void handleEvent(sf::Event event);
	void update(Int32 tpf);
	void setSpeed(float value) { speed = value; };
	virtual ~Player();
private:
	sf::RectangleShape shape;
	sf::Texture _texture;
	float speed;
	bool moveLeft;
	bool moveRight;
};
