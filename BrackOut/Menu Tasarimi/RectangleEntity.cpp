#include "RectangleEntity.hpp"


RectangleEntity::~RectangleEntity() {

}

void RectangleEntity::hit() {
	health--;
	setCrackedRectangleTexture(getBrickColor());
}

void RectangleEntity::update(Int32 tpf) {
	/*
		
		*/
}

// bricksleri konumlandirdim
void RectangleEntity::setPosition(float x, float y) {
	shape.setPosition(x, y);
}

void RectangleEntity::setColor(sf::Color c) {
	shape.setFillColor(c);
}

String RectangleEntity::getBrickColor() {
	renk = RENK(rand() % 5);
	
	String secilen = " ";
	sf::Texture t;

	switch (renk)
	{
	case RENK::BLUE:
		secilen = "blue";
		break;
	case RENK::GREEN:
		secilen = "green";
		break;
	case RENK::VIOLET:
		secilen = "violet";
		break;
	case RENK::YELLOW:
		secilen = "yellow";
		break;
	case RENK::PINK:
		secilen = "pink";
		break;
	default: secilen = "blue";
		break;
	}
	return secilen;
}

String RectangleEntity::getPlayerColor() {
	srand(time(0));
	renk = RENK(rand() % 5);
	String secilen = " ";
	sf::Texture t;

	switch (renk)
	{
	case RENK::BLUE:
		secilen = "blue";
		break;
	case RENK::GREEN:
		secilen = "black";
		break;
	case RENK::VIOLET:
		secilen = "orange";
		break;
	case RENK::YELLOW:
		secilen = "yellow";
		break;
	case RENK::PINK:
		secilen = "pink";
		break;
	default: secilen = "blue";
		break;
	}
	return secilen;
}

void RectangleEntity::setRectangleTexture(String renk) {
	if (!_texture.loadFromFile("./resimler/Bricks/brick_"+renk+"_small.png"))
		printf("%s", "Texture yuklenmedi! Error!");
	shape.setTexture(&_texture);
	shape.setTextureRect(sf::IntRect(0, 0, 512, 512));
}

void RectangleEntity::setCrackedRectangleTexture(String renk) {
	if (!_texture.loadFromFile("./resimler/Bricks/brick_" + renk + "_small_cracked.png"))
		printf("%s", "Texture yuklenmedi! Error!");
	shape.setTexture(&_texture);
	shape.setTextureRect(sf::IntRect(0, 0, 512, 512));
}

void RectangleEntity::setPlayerTexture(String renk) {
	
	if (!_texture.loadFromFile("./resimler/Bats/bat_"+renk+".png"))
		printf("%s", "Texture yuklenmedi! Error!");
	shape.setTexture(&_texture);
	shape.setTextureRect(sf::IntRect(0, 0, 512, 512));
	
}


Vector2f RectangleEntity::getPosition() {
	return shape.getPosition();
}

void RectangleEntity::draw(RenderTarget& target) {
	target.draw(shape);
}
