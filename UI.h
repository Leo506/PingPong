#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
namespace UI {
	class UIController {
	public:
		UIController();
		void drawUI(sf::RenderWindow& window, GAME::GameController& gameController);
		void gameOver(sf::RenderWindow& window);
		void win(sf::RenderWindow& window);

	private:
		sf::Texture hpIcon;
		sf::Sprite hp[3];
		sf::Text gameOverText;
		sf::Text winText;
		sf::Font font;
	};
}