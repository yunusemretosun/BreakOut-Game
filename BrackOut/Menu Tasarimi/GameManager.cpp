#include <algorithm>
#include "SFML/Graphics.hpp"

#include "GameManager.hpp"
#include "Player.hpp"
#include<iostream>
using namespace sf;



bool isDestroyed(RectangleEntity *e) {
	/*std::cout << e->getHealth() << std::endl;
	koruma amacli kontrol
	*/
	if (e->getHealth() <= 0)
		return true;
	else
		return false;
}
GameManager::GameManager(RenderWindow& w)
	: window(w), player(NULL), ball(NULL)
{

}

void GameManager::handleBrickCollision(const sf::FloatRect& ballBounds) {
	// bricklerin carpisma kontrolu
	for (RectangleEntity* b : entities) {
		FloatRect in;
		sf::FloatRect bb = b->getShape().getGlobalBounds();
		if (ballBounds.intersects(bb, in)) {
			if (abs((in.top + in.height) - (bb.top + bb.height)) < 0.001) {
				//brickin altina vur - asagi zipla
				ball->setYVelocity(abs(ball->getYVelocity()));
				b->hit();
			}
			else if (abs((in.top) - (bb.top)) < 0.001) {
				// brickin ustune vur - yukari zipla
				ball->setYVelocity(-abs(ball->getYVelocity()));
				b->hit();
			}
			else if (abs((in.left) - (bb.left)) < 0.001) {
				// soluna vur - sola 
				ball->setXVelocity(-abs(ball->getXVelocity()));
				//b->hit();
			}
			else if (abs((in.left + in.width) - (bb.left + bb.width)) < 0.001) {
				// sagina vur - saga
				ball->setXVelocity(abs(ball->getXVelocity()));
				//b->hit();
			}
		}
	}
	// olen brickleri silme
	entities.erase(
		std::remove_if(entities.begin(), entities.end(), isDestroyed),
		entities.end());
}

void GameManager::handleCollision() {
	sf::Vector2u wSize = window.getSize();

	// top ve player kontrolu

	sf::FloatRect ballBounds = ball->getShape().getGlobalBounds();
	sf::FloatRect playerBounds = player->getShape().getGlobalBounds();

	if (ballBounds.intersects(playerBounds)) {
		ball->setYVelocity(-abs(ball->getYVelocity()));
		const sf::Vector2f pos = ball->getShape().getPosition();

		// topu oyuncuya atar
		ball->setPosition(pos.x, playerBounds.top - ballBounds.height);

		// topun playera vurdugu yere bagli olarak topun hizini degistirir
		float paddleCenter = playerBounds.left + playerBounds.width / 2;
		float ballCenter = ballBounds.left + ballBounds.width / 2;

		float diff = ballCenter - paddleCenter;

		float fact = 1 / (playerBounds.width / 2) * diff;
		float velChange = 200 * fact;

		float xVel = ball->getXVelocity();
		ball->setXVelocity(std::min(xVel + velChange, ball->getMaxVel()));
	}

	// oyuncu ile duvar
	if (playerBounds.left < 0) {
		player->setPosition(0, player->getPosition().y);
	}
	if (playerBounds.left + playerBounds.width > wSize.x) {
		player->setPosition(wSize.x - playerBounds.width, player->getPosition().y);
	}

	//  duvarlar ve top
	if (ballBounds.left < 0) {
		// saga zipla
		ball->setXVelocity(abs(ball->getXVelocity()));

		// konumu duvarin kenarina sifirla
		ball->setPosition(0, ballBounds.top);
	}

	if (ballBounds.left + ballBounds.width > wSize.x) {
		// sola zipla
		ball->setXVelocity(-abs(ball->getXVelocity()));
		// konumu duvarin kenarina sifirla
		ball->setPosition(wSize.x - ballBounds.width, ballBounds.top);
	}

	if (ballBounds.top < 0) {
		// asagi zipla
		ball->setYVelocity(abs(ball->getYVelocity()));
		// yine konumu duvarin kenarina sifirla
		ball->setPosition(ballBounds.left, 0);
	}

	// bricklerele top arasindaki carpisma kontrolu
	handleBrickCollision(ballBounds);
}


void GameManager::handleEvent(Event& e) {
	if ((e.type == Event::KeyPressed && e.key.code == Keyboard::Escape) ||
		e.type == Event::Closed) {
		window.close();
		return;
	}

	if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space) {
		// top pozisyonunu resetleme
		ball->setPosition(player->getPosition().x + 20, player->getPosition().y - 20);
	}

	if (e.type == Event::KeyPressed || e.type == Event::KeyReleased) {
		player->handleEvent(e);
	}
}

void GameManager::update(Int32 tpf) {

	// guncelleme kismi
	for (RectangleEntity* e : entities) {
		e->update(tpf);
	}

	player->update(tpf);
	ball->update(tpf);

	handleCollision();

}

void GameManager::draw(sf::Sprite s) {
	// ekran temizleme
	window.clear();

	

	window.draw(s);
	// butun nesneleri cizelim
	for (RectangleEntity* p : this->entities) {
		p->draw(window);
	}
	player->draw(window);
	ball->draw(window);
	window.display();
}

void GameManager::createEntities() {
	//player'i olusturalim
	
	player = new Player(100, 50);

	player->setColor(sf::Color::White);
	player->setPlayerTexture(player->getPlayerColor());
	player->setPosition(window.getSize().x / 2, window.getSize().y - 60);
	player->setSpeed(600);


	
	// Brickler ve topu olusturma
	createBricks(5, 3, 10.0f, 50.0f);

	createBall(10, 10, 250);
}

void GameManager::createBall(float radius, int pc, float speed) {
	sf::Vector2u size = window.getSize();

	ball = new Ball(radius, pc, speed);
	ball->setPosition(size.x / 3, size.y - 250);

}

void GameManager::createBricks(int cols, int rows, float spacing, float brickHeight) {

	// ekran boyutu
	sf::Vector2u screen = window.getSize();

	// her brick arasina bosluk koyma
	float sumSpacing = (cols + 1) * spacing;
	// bricklerin uzunlugunu tutma
	float brickLength = (screen.x - sumSpacing) / cols;

	// ilk brickin baslama noktasi
	int posX = spacing;
	int posY = 50;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			RectangleEntity* e = new RectangleEntity(brickLength, brickHeight);
			e->setPosition(posX, posY);
			e->setRectangleTexture(e->getBrickColor());
			
			entities.push_back(e);

			posX += brickLength + spacing;
		}
		posX = spacing;
		posY += brickHeight + spacing;
	}

}

GameManager::~GameManager() {

	for (RectangleEntity* e : entities) {
		delete e;
	}
	delete ball;
}

