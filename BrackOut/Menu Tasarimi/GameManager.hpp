#pragma once
#include <vector>

#include "SFML/Graphics.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "RectangleEntity.hpp"

using namespace sf;

class GameManager {
public:
	GameManager(RenderWindow &w);

	void update(Int32 tpf);
	void draw(sf::Sprite s);
	void handleEvent(Event &e);

	void handleCollision();

	void createEntities();


	virtual ~GameManager();

private:
	RenderWindow &window;
	Player *player;
	Ball *ball;
	
	std::vector<RectangleEntity*> entities;

	//Player* createPlayer();
	
	void createBricks(int sutun, int satir, float bosluk, float brickHeight);
	void createBall(float radius, int pc, float speed);
	void handleBrickCollision(const sf::FloatRect& ballBounds);
	
};
