#include "credits.h"

#include "sl.h"

#include "utils/math.h"
#include "utils/Rectangles.h"
#include "utils/collisions.h"
#include "utils/fonts.h"
#include "constants.h"

namespace CreditsScreen {
	static const double MARGIN = 75;
	static const double GO_BACK_WIDTH = 150;
	static const double GO_BACK_HEIGHT = 100;

	static const Rectangles::Rectangle goBackRectangle = {
		MARGIN + MathUtils::getHalf(GO_BACK_WIDTH),
		MARGIN + MathUtils::getHalf(GO_BACK_HEIGHT),
		GO_BACK_WIDTH,
		GO_BACK_HEIGHT
	};


	void drawCredits() {
		int titleFontSize = 60;
		int textFontSize = 40;

		const char* developersTitle = "DEVELOPERS";
		const char* developerText = "Maximiliano Feldman";

		Fonts::writeText(
			developersTitle,
			{ MARGIN, Constants::SCREEN_DIMENSIONS.y - MARGIN * 2 },
			Colors::YELLOW,
			titleFontSize
		);

		Fonts::writeText(
			developerText,
			{ MARGIN, Constants::SCREEN_DIMENSIONS.y - MARGIN * 3 },
			Colors::WHITE,
			titleFontSize
		);

		Vectors::Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };

		Rectangles::fillRectangle(
			goBackRectangle,
			Collisions::checkPointToRectangleCollision(goBackRectangle, mousePosition) ? Colors::DARK_RED : Colors::RED
		);

		const char* goBackText = "Go back";
		int goBackFontSize = 30;

		Fonts::setFontSize(goBackFontSize);
		Vectors::Vector2 goBackTextSize = Fonts::getTextSize(goBackText);

		Fonts::writeText(
			goBackText,
			{ goBackRectangle.xCenter - MathUtils::getHalf(goBackTextSize.x), goBackRectangle.yCenter - MathUtils::getHalf(goBackTextSize.y) },
			Colors::WHITE,
			goBackFontSize
		);
	};

	void changeScreen(Screen::Screen& screen) {
		Vectors::Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };

		if (Collisions::checkPointToRectangleCollision(goBackRectangle, mousePosition) && slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
			screen = Screen::MENU;
		}
	};
}
