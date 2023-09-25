#include "rules.h"

#include "sl.h"

#include "utils/fonts.h"
#include "utils/circles.h"
#include "entities/powerup.h"
#include "constants.h"
#include "utils/math.h"
#include "utils/Rectangles.h"
#include "utils/collisions.h"

namespace RulesScreen {
	static const double MARGIN = 75;
	static const double GO_BACK_WIDTH = 150;
	static const double GO_BACK_HEIGHT = 100;

	static const Rectangles::Rectangle goBackRectangle = {
		MARGIN + MathUtils::getHalf(GO_BACK_WIDTH),
		MARGIN + MathUtils::getHalf(GO_BACK_HEIGHT),
		GO_BACK_WIDTH,
		GO_BACK_HEIGHT
	};

	static struct PowerUpWithText {
		Colors::Color color;
		const char* text;
	};

	void drawRules() {
		const double FONT_SIZE = 30;

		Fonts::setFontSize(FONT_SIZE);

		const int FIRST_TEXTS_COUNT = 3;
		const char* movementText = "Move with A and D.";
		const char* objectiveText = "Your objective is to break all blocks. When you break all blocks, you win!";
		const char* powerUpsTitle = "POWER UPS:";
	
		const char* firstTexts[] = {
			movementText,
			objectiveText,
			powerUpsTitle
		};

		for (int i = 0; i < FIRST_TEXTS_COUNT; i++) {
			Fonts::writeText(
				firstTexts[i],
				{ MARGIN, Constants::SCREEN_DIMENSIONS.y - MARGIN - MARGIN * i },
				Colors::WHITE,
				FONT_SIZE
			);
		}

		const PowerUpWithText enlargeText = { Colors::GREEN, "Makes your paddle bigger." };
		const PowerUpWithText reduceText = { Colors::DARK_RED, "Makes your paddle smaller." };
		const PowerUpWithText addBallText = { Colors::YELLOW, "Adds a ball!" };

		const int POWER_UP_TEXTS_COUNT = 3;
		const double PLUS_MARGIN = 50;
		const PowerUpWithText powerUpTexts[POWER_UP_TEXTS_COUNT] = {
			enlargeText,
			reduceText,
			addBallText
		};

		for (int i = 0; i < POWER_UP_TEXTS_COUNT; i++) {
			Circles::drawCircle(
				{
					MARGIN + PowerUps::POWER_UP_RADIUS,
					Constants::SCREEN_DIMENSIONS.y - FIRST_TEXTS_COUNT * MARGIN - MARGIN - MARGIN * i
				}, 
				PowerUps::POWER_UP_RADIUS,
				powerUpTexts[i].color
			);

			Fonts::writeText(
				powerUpTexts[i].text,
				{
					MARGIN + PowerUps::POWER_UP_RADIUS * 3,
					Constants::SCREEN_DIMENSIONS.y - FIRST_TEXTS_COUNT * MARGIN - MARGIN - MARGIN * i - PowerUps::POWER_UP_RADIUS + MathUtils::getHalf(Fonts::getTextSize(powerUpTexts->text).y)
				},
				Colors::WHITE,
				FONT_SIZE
			);
		}

		const char* randomlyGeneratedText = "All levels are randomly generated!";

		Fonts::writeText(
			randomlyGeneratedText,
			{
				MARGIN,
				Constants::SCREEN_DIMENSIONS.y - (FIRST_TEXTS_COUNT + POWER_UP_TEXTS_COUNT) * MARGIN - MARGIN
			},
			Colors::WHITE,
			FONT_SIZE
		);

		Vectors::Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };

		Rectangles::fillRectangle(
			goBackRectangle,
			Collisions::checkPointToRectangleCollision(goBackRectangle, mousePosition) ? Colors::DARK_RED : Colors::RED
		);

		const char* goBackText = "Go back";
		Vectors::Vector2 goBackTextSize = Fonts::getTextSize(goBackText);

		Fonts::writeText(
			goBackText,
			{ goBackRectangle.xCenter - MathUtils::getHalf(goBackTextSize.x), goBackRectangle.yCenter - MathUtils::getHalf(goBackTextSize.y) },
			Colors::WHITE,
			FONT_SIZE
		);
	}

	void changeScreen(Screen::Screen& screen) {
		Vectors::Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };

		if (Collisions::checkPointToRectangleCollision(goBackRectangle, mousePosition) && slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
			screen = Screen::MENU;
		}
	};
}
