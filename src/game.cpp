#include "sl.h"
#include "utils/fonts.h"
#include "screens/screens.h"
#include "screens/menu.h"
#include "screens/rules.h"
#include "screens/gameplay.h"
#include "screens/credits.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>

namespace Game {
	bool isLeftClickPressed = false;

	static void init() {
		srand(time(NULL));
		slWindow(Constants::SCREEN_DIMENSIONS.x, Constants::SCREEN_DIMENSIONS.y, "LeBreakout", false);

		Fonts::initFont("src/white_rabbit.ttf");
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
