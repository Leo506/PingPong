#include <SFML/Graphics.hpp>
#include "UI.h"
#include "Settings.h"
#include <iostream>

namespace UI {
	UIController::UIController() {
		hpIcon.loadFromFile("Sprites/HP.png");
		
		for (int i = 0; i < 3; i++)
		{
			hp[i].setTexture(hpIcon);
			hp[i].setPosition(OFFSET / 2 - 30, 50 * i);
		}


		font.loadFromFile("Font/Roboto-Regular.ttf");

		gameOverText.setString("\tGAME OVER\nPress space to start again");
		gameOverText.setFont(font);
		gameOverText.setCharacterSize(24);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setStyle(sf::Text::Bold);
		gameOverText.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2);
	}

	void UIController::drawUI(sf::RenderWindow& window, GAME::GameController& gameController) {
		if (gameController.getHPCount() > 0) {
			for (int i = 0; i < gameController.getHPCount(); i++)
			{
				window.draw(hp[i]);

			}
		}
	}

	void UIController::gameOver(sf::RenderWindow& window) {

		window.draw(gameOverText);
	}
}