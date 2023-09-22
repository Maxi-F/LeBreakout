#include "sl.h"
#include "utils/fonts.h"
#include "screens/screens.h"
#include "screens/menu.h"
#include "screens/gameplay.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>

static void init() {
	srand(time(NULL));
	slWindow(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, "LeBreakout", false);

	initFont("src/white_rabbit.ttf");
	initMenu();
}

static void doActionBySelectedOption(Screen& actualScreen, bool& shouldClose) {
	checkOptionCollisions();

	Option selectedOption = getPressedOption();

	switch (selectedOption) {
	case Option::NONE:
		break;
	case Option::EXIT:
		shouldClose = true;
		break;
	case Option::GAME_RULES:
		actualScreen = Screen::RULES;
		break;
	case Option::PLAY:
		actualScreen = Screen::GAMEPLAY;
		initGameplay();
		break;
	case Option::GAME_CREDITS:
		actualScreen = Screen::CREDITS;
		break;
	}
}


static void screenLoop(Screen &actualScreen, bool& shouldClose) {
	switch (actualScreen) {
		case Screen::MENU:
			doActionBySelectedOption(actualScreen, shouldClose);
			drawMenu();
			break;
		case Screen::GAMEPLAY:
			updateGameplay();
			drawGameplay();
			break;
		case Screen::RULES:
			break;
	}
}

void startGame() {
	init();
	Screen actualScreen = Screen::MENU;
	bool shouldClose = false;

	while (!slShouldClose() && !shouldClose)
	{
		screenLoop(actualScreen, shouldClose);

		slRender();
	}

	slClose();
}
