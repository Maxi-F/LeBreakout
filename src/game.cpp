#include "sl.h"
#include "utils/fonts.h"
#include "screens/screens.h"
#include "screens/menu.h"
#include "constants.h"

static void init() {
	slWindow(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, "LeBreakout", false);

	initFont("src/white_rabbit.ttf");
	initMenu();
}

static void screenLoop(Screen actualScreen) {
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

static void screenTransition(Screen& actualScreen, bool& shouldClose) {
	switch (actualScreen) {
		case Screen::MENU:
			doActionBySelectedOption(actualScreen, shouldClose);
			break;
		case Screen::GAMEPLAY:
			break;
		case Screen::CREDITS:
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
		screenLoop(actualScreen);

		screenTransition(actualScreen, shouldClose);
		slRender();
	}

	slClose();
}
