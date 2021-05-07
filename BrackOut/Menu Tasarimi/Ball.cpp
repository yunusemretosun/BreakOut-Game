#include "Ball.hpp"

sf::Sprite ballSprite;
sf::Texture kaplama;
Ball::Ball(int radius, int pointCount, float speed) :
		xVelocity(speed*0.8), yVelocity(speed*1.2), maxVel(500)
{
	shape = CircleShape(radius, pointCount);

	_color = sf::Color::White;
	shape.setFillColor(_color);
	shape.setOutlineThickness(0);
	shape.setOrigin(0, 0);
	String renk;
	String renkDizisi[] = { "blue","green","yellow","red","orange","silver" };

	srand(time(0));
	renk = renkDizisi[rand() % 6];

	if (!_texture.loadFromFile("./resimler/Balls/ball_" + renk + ".png"))
		printf("%s", "Texture yuklenmedi! Error!");
	shape.setTexture(&_texture);
	shape.setTextureRect(sf::IntRect(0, 0, 512, 512));
	
}

void Ball::update(Int32 tpf) {

	// mevcut hareketi heseaplama
	float xVel = xVelocity * (tpf / 1000.0f);
	float yVel = yVelocity * (tpf / 1000.0f);

	const sf::Vector2f pos = shape.getPosition();

	shape.setPosition(pos.x + xVel, pos.y + yVel);
	


}

void Ball::setBallTexture() {
	String renk;
	String renkDizisi[] = { "blue","green","yellow","red","orange","silver" };

	srand(time(0));
	renk = renkDizisi[rand() % 6];

	if (!_texture.loadFromFile("./resimler/Balls/ball_" + renk + ".png"))
		printf("%s", "Texture yuklenmedi! Error!");
	shape.setTexture(&_texture);
	shape.setTextureRect(sf::IntRect(0, 0, 512, 512));

}

void Ball::setPosition(float x, float y) {
	shape.setPosition(x, y);
}

void Ball::draw(RenderTarget& target) {
	
	target.draw(shape);

}



Ball::~Ball() {
}

