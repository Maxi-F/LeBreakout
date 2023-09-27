#include "game.h"

#include <stdlib.h>
#include <time.h>

#include "sl.h"

#include "utils/fonts.h"
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

		static void init() {
			srand(static_cast<unsigned int>(time(NULL)));
		
			slWindow(
				static_cast<int>(Constants::SCREEN_DIMENSIONS.x),
				static_cast<int>(Constants::SCREEN_DIMENSIONS.y),
				"LeBreakout",
				true
			);

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
					Menu::drawMenu();
					break;
				case Screen::GAMEPLAY:
					Gameplay::updateGameplay(actualScreen, isLeftClickPressed);
					Gameplay::drawGameplay();
					break;
				case Screen::RULES:
					RulesScreen::drawRules();
					RulesScreen::changeScreen(actualScreen);
					break;
				case Screen::CREDITS:
					CreditsScreen::drawCredits();
					CreditsScreen::changeScreen(actualScreen);
					break;
			}
		}

		void startGame() {
			init();
			Screen::Screen actualScreen = Screen::MENU;
			bool shouldClose = false;

			while (!slShouldClose() && !shouldClose)
			{
				screenLoop(actualScreen, shouldClose);

				slRender();
			}

			slClose();
		}
	}
}
