#include "game.h"

#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "utils/fonts.h"
#include "window.h"
#include "screens/screens.h"
#include "screens/menu.h"
#include "screens/rules.h"
#include "screens/gameplay.h"
#include "screens/credits.h"
#include "textureManager.h"
#include "constants.h"

namespace LeBreakout {
	namespace Game {
		bool isLeftClickPressed = false;
		extern sf::Clock deltaClock;

		static void init() {
			srand(static_cast<unsigned int>(time(NULL)));

			TextureManager::initTextureManager();
			Fonts::initFont("assets/amatic.ttf");
			Menu::initMenu();
		}

		static void doActionBySelectedOption(sf::RenderWindow& window, Screen::Screen& actualScreen, bool& shouldClose) {
			Menu::checkOptionCollisions(window, isLeftClickPressed);

			Menu::Option selectedOption = Menu::getPressedOption();

			switch (selectedOption) {
			case Menu::Option::NONE:
				break;
			case Menu::Option::EXIT:
				shouldClose = true;
				break;
			case Menu::Option::GAME_RULES:
				actualScreen = Screen::RULES;
				break;
			case Menu::Option::PLAY:
				actualScreen = Screen::GAMEPLAY;
				Gameplay::initGameplay();
				break;
			case Menu::Option::GAME_CREDITS:
				actualScreen = Screen::CREDITS;
				break;
			}
		}


		static void screenLoop(sf::RenderWindow& window, Screen::Screen &actualScreen, bool& shouldClose) {
			switch (actualScreen) {
				case Screen::MENU:
					doActionBySelectedOption(window, actualScreen, shouldClose);
					window.clear();
						Menu::drawMenu(window);
					window.display();
					break;
				case Screen::GAMEPLAY:
					Gameplay::updateGameplay(window, actualScreen, isLeftClickPressed);
					window.clear();
						Gameplay::drawGameplay(window);
					window.display();
					break;
				case Screen::RULES:
					window.clear();
						RulesScreen::drawRules(window);
					window.display();
					RulesScreen::changeScreen(window, actualScreen);
					break;
				case Screen::CREDITS:
					window.clear();
						CreditsScreen::drawCredits(window);
					window.display();
					CreditsScreen::changeScreen(window, actualScreen);
					break;
			}
		}

		void startGame() {
			init();
			sf::RenderWindow window(sf::VideoMode(Constants::SCREEN_DIMENSIONS.x, Constants::SCREEN_DIMENSIONS.y), "LeBreakout");
			Screen::Screen actualScreen = Screen::MENU;

			bool shouldClose = false;
			sf::Clock clock;
			while (window.isOpen() && !shouldClose)
			{
				// Process events
				sf::Event event;
				while (window.pollEvent(event))
				{
					// Close window: exit
					if (event.type == sf::Event::Closed)
						window.close();
				}

				sf::Time dt = clock.restart();
				Window::deltaTime = dt.asSeconds();
				screenLoop(window, actualScreen, shouldClose);
			}
		}
	}
}
