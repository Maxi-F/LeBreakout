#include "sl.h"
#include "menu.h"
#include "screens.h"
#include "../constants.h"
#include "../utils/collisions.h"
#include "../utils/Rectangles.h"
#include "../utils/Colors.h"
#include "../utils/fonts.h"
#include "../utils/math.h"
#include "../utils/Vector.h"

#define MENU_OPTIONS_LENGTH 4

static struct MenuOption {
	Option option;
	Rectangle rectangle;
	const char* optionText;
	bool isClicked = false;
	bool isHovered = false;
};

static MenuOption menuOptions[MENU_OPTIONS_LENGTH];

const Vector2 HALF_SCREEN = { getHalf(SCREEN_DIMENSIONS.x), getHalf(SCREEN_DIMENSIONS.y) };
const double OPTION_WIDTH = 300.0;
const double OPTION_HEIGHT = 100.0;
const double OPTION_MARGIN = 20.0;
const int OPTION_FONT_SIZE = 60;

void initMenu() {
	Rectangle playRectangle = { 
		HALF_SCREEN.x,
		HALF_SCREEN.y + OPTION_HEIGHT + OPTION_MARGIN,
		OPTION_WIDTH,
		OPTION_HEIGHT
	};

	Rectangle rulesRectangle = {
		HALF_SCREEN.x,
		HALF_SCREEN.y,
		OPTION_WIDTH,
		OPTION_HEIGHT
	};

	Rectangle creditsRectangle = {
		HALF_SCREEN.x,
		HALF_SCREEN.y - OPTION_HEIGHT - OPTION_MARGIN,
		OPTION_WIDTH,
		OPTION_HEIGHT
	};

	Rectangle exitRectangle = {
		HALF_SCREEN.x,
		HALF_SCREEN.y - OPTION_HEIGHT * 2 - OPTION_MARGIN * 2,
		OPTION_WIDTH,
		OPTION_HEIGHT
	};

	MenuOption newMenuOptions[MENU_OPTIONS_LENGTH] = {
		{
			Option::PLAY,
			playRectangle,
			"Play"
		},
		{
			Option::GAME_RULES,
			rulesRectangle,
			"Rules"
		},
		{
			Option::GAME_CREDITS,
			creditsRectangle,
			"Credits"
		},
		{
			Option::EXIT,
			exitRectangle,
			"Exit"
		}
	};

	for (int i = 0; i < MENU_OPTIONS_LENGTH; i++) {
		menuOptions[i] = newMenuOptions[i];
	}
}

void checkOptionCollisions() {
	Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };

	for (int i = 0; i < MENU_OPTIONS_LENGTH; i++) {
		if (checkPointToRectangleCollision(menuOptions[i].rectangle, mousePosition)) {
			menuOptions[i].isHovered = true;

			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
				menuOptions[i].isClicked = true;
			}
		}
		else {
			menuOptions[i].isHovered = false;
		}
	}
}

void drawMenu() {
	setBackColor(BLACK);
	const char* title = "LeBreakout";
	int titleFontSize = 120;
	double titleMargin = 200;

	setFontSize(titleFontSize);

	writeText(
		title,
		{ HALF_SCREEN.x - getHalf(slGetTextWidth(title)), SCREEN_DIMENSIONS.y - titleMargin },
		WHITE,
		titleFontSize
	);

	setFontSize(OPTION_FONT_SIZE);

	for (int i = 0; i < MENU_OPTIONS_LENGTH; i++) {
		const char* optionText = menuOptions[i].optionText;
		Rectangle optionRectangle = menuOptions[i].rectangle;

		fillRectangle(optionRectangle, menuOptions[i].isHovered ? DARK_RED : RED);
		writeText(
			optionText,
			{ 
				optionRectangle.xCenter - getHalf(slGetTextWidth(optionText)),
				optionRectangle.yCenter - getHalf(slGetTextHeight(optionText))
			},
			WHITE,
			OPTION_FONT_SIZE
		);
	};
}

Option getPressedOption() {
	Option selectedOption = Option::NONE;

	for (int i = 0; i < MENU_OPTIONS_LENGTH; i++) {
		if (menuOptions[i].isClicked) {
			selectedOption = menuOptions[i].option;
		}
	}

	return selectedOption;
}
