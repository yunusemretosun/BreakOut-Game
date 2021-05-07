/*
*Yunus Emre Tosun 
* if u don't understand the comments use translater. :)
*/


#include <iostream>
#include "SFML/Graphics.hpp"

#include "GameManager.hpp"
#include "Player.hpp"

using namespace sf;

int main(int argc, char **argv)
{
	std::cout << "oyun basliyor ..." << std::endl;
	RenderWindow window(VideoMode(400, 600), "Breakout");
	window.setVerticalSyncEnabled(true);
	Texture t;
	t.loadFromFile("./resimler/Background/background.jpg");
	sf::Sprite s(t);

	// game manager cizilecek nesnelerin pointerlarini tutar.
	GameManager manager(window);
	manager.createEntities();

	Clock clock;
	while(window.isOpen()) {
		Event e;
		while(window.pollEvent(e)) {
			manager.handleEvent(e);
		}

		sf::Time elapsed = clock.restart();
		sf::Int32 tpf = elapsed.asMilliseconds();
		
		manager.update(tpf);
		manager.draw(s);
		
	}

	return 0;
}



