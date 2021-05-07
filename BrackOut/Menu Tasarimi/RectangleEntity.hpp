#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

using namespace sf;

//cizilecek temel sekil
enum class RENK{BLUE,GREEN,PINK,VIOLET,YELLOW};
class RectangleEntity {
private:
	RENK renk;
	sf::RectangleShape shape;
	sf::Color _color;
	sf::Texture _texture;
	sf::Sprite _rects;
	bool destroyed;
	int health;

public:
	RectangleEntity(float w, float h){
		shape = RectangleShape(Vector2f(w, h));
		health = 2;
		destroyed = false;
		
	}

	virtual ~RectangleEntity();

	void draw(RenderTarget& target);
	virtual void update(Int32 tpf);

	void setColor(sf::Color c);

	String getBrickColor();

	String getPlayerColor();

	void setRectangleTexture(String renk);

	void setCrackedRectangleTexture(String renk);

	void setPlayerTexture(String renk);
	
	void setPosition(float x, float y);
	Vector2f getPosition();
	RectangleShape getShape() { return shape; }
	sf::Texture getTexture(){ return _texture; }
	sf::FloatRect GetBounds() const { return shape.getGlobalBounds(); }
	void hit();
	int getHealth() { return health; }


};

