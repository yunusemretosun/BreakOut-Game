#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Ball {
public:
	Ball(int radius, int pointCount, float speed );
	void draw(RenderTarget& target);
	void update (Int32 tpf);
	void setBallTexture();
	void setPosition(float x, float y);


	virtual ~Ball();

	CircleShape getShape() {return shape;};
	float getXVelocity() {return xVelocity;};
	float getYVelocity() {return yVelocity;};
	void setXVelocity(float value) { xVelocity = value;}
	void setYVelocity(float value) { yVelocity = value;}

	float getMaxVel() {return maxVel;}
private:
	sf::CircleShape shape;
	sf::Color _color;
	sf::Texture _texture;
	

	// mevcut x/y velocity
	float xVelocity;
	float yVelocity;

	float maxVel;
};

