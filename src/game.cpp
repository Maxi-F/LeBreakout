#include "sl.h"
#include "utils/fonts.h"
#include "screens/screens.h"
#include "screens/menu.h"
#include "constants.h"

void init() {
	slWindow(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, "LeBreakout", false);

	initFont("src/white_rabbit.ttf");
	initMenu();
}

void screenLoop(Screen &actualScreen) {
	switch (actualScreen) {
		case Screen::MENU:
			drawMenu();
			break;
		case Screen::GAMEPLAY:
			break;
		case Screen::RULES:
			break;
	}
}

void startGame() {
	init();
	Screen actualScreen = Screen::MENU;

	while (!slShouldClose())
	{
		screenLoop(actualScreen);

		slRender();
	}

	slClose();
}
