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

			Window::init();
			TextureManager::initTextureManager();
			Fonts::initFont("assets/amatic.ttf");
			Menu::initMenu();
		}

		static void doActionBySelectedOption(Screen::Screen& actualScreen, bool& shouldClose) {
			Menu::checkOptionCollisions(isLeftClickPressed);

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


		static void screenLoop(Screen::Screen &actualScreen, bool& shouldClose) {
			switch (actualScreen) {
				case Screen::MENU:
					doActionBySelectedOption(actualScreen, shouldClose);
					Window::window.clear();
						Menu::drawMenu();
					Window::window.display();
					break;
				case Screen::GAMEPLAY:
					Gameplay::updateGameplay(actualScreen, isLeftClickPressed);
					Window::window.clear();
						Gameplay::drawGameplay();
					Window::window.display();
					break;
				case Screen::RULES:
					Window::window.clear();
						RulesScreen::drawRules();
					Window::window.display();
					RulesScreen::changeScreen(actualScreen);
					break;
				case Screen::CREDITS:
					Window::window.clear();
						CreditsScreen::drawCredits();
					Window::window.display();
					CreditsScreen::changeScreen(actualScreen);
					break;
			}
		}

		void startGame() {
			init();
			Screen::Screen actualScreen = Screen::MENU;

			bool shouldClose = false;
			sf::Clock clock;
			while (Window::window.isOpen() && !shouldClose)
			{
				sf::Time dt = clock.restart();
				Window::deltaTime = dt.asSeconds();
				screenLoop(actualScreen, shouldClose);
			}
		}
	}
}
