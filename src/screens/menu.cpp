#include "sl.h"
#include "menu.h"
#include "screens.h"
#include "constants.h"
#include "utils/collisions.h"
#include "utils/Rectangles.h"
#include "utils/Colors.h"
#include "utils/fonts.h"
#include "utils/math.h"
#include "utils/Vector.h"

namespace Menu {
	static const int MENU_OPTIONS_LENGTH = 4;

	static struct MenuOption {
		Option option;
		Rectangles::Rectangle rectangle;
		const char* optionText;
		bool isClicked = false;
		bool isHovered = false;
	};

	static MenuOption menuOptions[MENU_OPTIONS_LENGTH];

	const Vectors::Vector2 HALF_SCREEN = { MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x), MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y) };
	const double OPTION_WIDTH = 300.0;
	const double OPTION_HEIGHT = 100.0;
	const double OPTION_MARGIN = 20.0;
	const int OPTION_FONT_SIZE = 60;

	void initMenu() {
		Rectangles::Rectangle playRectangle = { 
			HALF_SCREEN.x,
			HALF_SCREEN.y + OPTION_HEIGHT + OPTION_MARGIN,
			OPTION_WIDTH,
			OPTION_HEIGHT
		};

		Rectangles::Rectangle rulesRectangle = {
			HALF_SCREEN.x,
			HALF_SCREEN.y,
			OPTION_WIDTH,
			OPTION_HEIGHT
		};

		Rectangles::Rectangle creditsRectangle = {
			HALF_SCREEN.x,
			HALF_SCREEN.y - OPTION_HEIGHT - OPTION_MARGIN,
			OPTION_WIDTH,
			OPTION_HEIGHT
		};

		Rectangles::Rectangle exitRectangle = {
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
		Vectors::Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };

		for (int i = 0; i < MENU_OPTIONS_LENGTH; i++) {
			if (Collisions::checkPointToRectangleCollision(menuOptions[i].rectangle, mousePosition)) {
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
		setBackColor(Colors::BLACK);
		const char* title = "LeBreakout";
		int titleFontSize = 120;
		double titleMargin = 200;

		Fonts::setFontSize(titleFontSize);

		Fonts::writeText(
			title,
			{ HALF_SCREEN.x - MathUtils::getHalf(slGetTextWidth(title)), Constants::SCREEN_DIMENSIONS.y - titleMargin },
			Colors::WHITE,
			titleFontSize
		);

		Fonts::setFontSize(OPTION_FONT_SIZE);

		for (int i = 0; i < MENU_OPTIONS_LENGTH; i++) {
			const char* optionText = menuOptions[i].optionText;
			Rectangles::Rectangle optionRectangle = menuOptions[i].rectangle;

			Rectangles::fillRectangle(optionRectangle, menuOptions[i].isHovered ? Colors::DARK_RED : Colors::RED);
			Fonts::writeText(
				optionText,
				{ 
					optionRectangle.xCenter - MathUtils::getHalf(slGetTextWidth(optionText)),
					optionRectangle.yCenter - MathUtils::getHalf(slGetTextHeight(optionText))
				},
				Colors::WHITE,
				OPTION_FONT_SIZE
			);
		};
	}

	Option getPressedOption() {
		Option selectedOption = Option::NONE;

		for (int i = 0; i < MENU_OPTIONS_LENGTH; i++) {
			if (menuOptions[i].isClicked) {
				selectedOption = menuOptions[i].option;
				menuOptions[i].isClicked = false;
			}
		}

		return selectedOption;
	}
}
