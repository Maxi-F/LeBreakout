#include "screens/draws/gameplayDraws.h"

#include "sl.h"
#include <string>

#include "utils/Rectangles.h"
#include "utils/math.h"
#include "utils/vector.h"
#include "utils/fonts.h"
#include "utils/collisions.h"
#include "entities/paddle.h"
#include "entities/ball.h"
#include "entities/block.h"
#include "constants.h"

namespace GameplayDraws {
	extern const int GAMEPLAY_MENU_OPTIONS_LENGTH = 2;
	static const double MENU_OPTION_WIDTH = 300;
	static const double MENU_OPTION_HEIGHT = 100;
	static const double MENU_OPTION_MARGIN = 50;

	extern const GameplayMenuOption PAUSE_OPTIONS[GAMEPLAY_MENU_OPTIONS_LENGTH] = {
		{
			{
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y) + MENU_OPTION_HEIGHT + MENU_OPTION_MARGIN,
				MENU_OPTION_WIDTH,
				MENU_OPTION_HEIGHT
			},
			GameplayOption::RESUME,
		},
		{
			{
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y) - MENU_OPTION_HEIGHT,
				MENU_OPTION_WIDTH,
				MENU_OPTION_HEIGHT
			},
			GameplayOption::GO_TO_MENU,
		},
	};

	extern const GameplayMenuOption LOSE_OR_WIN_OPTIONS[GAMEPLAY_MENU_OPTIONS_LENGTH] = {
		{
			{
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y) + MENU_OPTION_HEIGHT + MENU_OPTION_MARGIN,
				MENU_OPTION_WIDTH,
				MENU_OPTION_HEIGHT
			},
			GameplayOption::PLAY_AGAIN,
		},
		{
			{
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
				MENU_OPTION_WIDTH,
				MENU_OPTION_HEIGHT
			},
			GameplayOption::GO_TO_MENU,
		},
	};

	static const char* optionToString(GameplayOption option) {
		switch (option) {
			case GameplayOption::RESUME:
				return "RESUME";
			case GameplayOption::GO_TO_MENU:
				return "BACK TO MENU";
			case GameplayOption::PLAY_AGAIN:
				return "PLAY AGAIN";
		};
	}

	static void drawUI(Gameplay::GameplayEntities gameplayEntities) {
		Rectangles::Rectangle uiBackground = {
			MathUtils::getHalf(Constants::FIELD_DIMENSIONS.x),
			Constants::SCREEN_DIMENSIONS.y - MathUtils::getHalf(Constants::FIELD_Y_MARGIN),
			Constants::SCREEN_DIMENSIONS.x,
			Constants::FIELD_Y_MARGIN
		};

		Rectangles::fillRectangle(uiBackground, Colors::GRAY);

		const std::string livesPreText = "Lives: ";
		std::string lives = std::to_string(gameplayEntities.player.lives);
		std::string livesText = livesPreText + lives;


		Vectors::Vector2 livesTextSize = Fonts::getTextSize(livesText.c_str());

		double fontSize = 40;

		Fonts::writeText(
			livesText.c_str(),
			{ fontSize, Constants::FIELD_DIMENSIONS.y + MathUtils::getHalf(Constants::FIELD_Y_MARGIN) - MathUtils::getHalf(livesTextSize.y) },
			Colors::WHITE,
			fontSize
		);
	}

	void drawBox(const char* title, const GameplayMenuOption options[GAMEPLAY_MENU_OPTIONS_LENGTH]) {
		const Vectors::Vector2 MENU_SIZE = { 550, 700 };
		const Vectors::Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };

		Rectangles::Rectangle menu = {
			MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
			MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
			MENU_SIZE.x,
			MENU_SIZE.y
		};

		Rectangles::fillRectangle(menu, Colors::OPAQUE_BLACK);
		
		double titleFontSize = 50;
		double titleMargin = 60;
		Fonts::setFontSize(titleFontSize);

		Vectors::Vector2 titleSize = Fonts::getTextSize(title);

		Fonts::writeText(
			title,
			{ 
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x) - MathUtils::getHalf(titleSize.x),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y) + MathUtils::getHalf(MENU_SIZE.y) - titleSize.y - titleMargin
			},
			Colors::WHITE,
			titleFontSize
		);

		for (int i = 0; i < GAMEPLAY_MENU_OPTIONS_LENGTH; i++) {
			Rectangles::fillRectangle(
				options[i].rectangle,
				Collisions::checkPointToRectangleCollision(options[i].rectangle, mousePosition) ? 
					Colors::DARK_RED : 
					Colors::RED
			);

			const char* optionText = optionToString(options[i].option);

			double optionFontSize = 35;
			Fonts::setFontSize(optionFontSize);
			Vectors::Vector2 optionSize = Fonts::getTextSize(optionText);

			Fonts::writeText(
				optionText,
				{ 
					options[i].rectangle.xCenter - MathUtils::getHalf(optionSize.x),
					options[i].rectangle.yCenter - MathUtils::getHalf(optionSize.y)
				},
				Colors::WHITE,
				optionFontSize
			);
		}
	}

	void drawPause() {
		drawBox("PAUSED", PAUSE_OPTIONS);
	}

	void drawWinBox() {
		drawBox("You won!", LOSE_OR_WIN_OPTIONS);
	}

	void drawLoseBox() {
		drawBox("You lost...", LOSE_OR_WIN_OPTIONS);
	}

	void drawGameplay(Gameplay::GameplayEntities gameplayEntities) {

		Paddle::drawPaddle(gameplayEntities.paddle);

		for (int i = 0; i < gameplayEntities.balls.size(); i++) {
			Ball::drawBall(&gameplayEntities.balls[i]);
		}

		for (int i = 0; i < gameplayEntities.blockRows.size(); i++) {
			for (int j = 0; j < gameplayEntities.blockRows[i].size(); j++) {
				Block::drawBlock(gameplayEntities.blockRows[i][j]);
			}
		}

		// This is in another loop so it draws on top of the blocks
		for (int i = 0; i < gameplayEntities.blockRows.size(); i++) {
			for (int j = 0; j < gameplayEntities.blockRows[i].size(); j++) {
				PowerUps::drawPowerUp(gameplayEntities.blockRows[i][j].powerUp);
			}
		}

		drawUI(gameplayEntities);

		if (gameplayEntities.hasLost) drawLoseBox();
		if (gameplayEntities.hasWon) drawWinBox();
		if (gameplayEntities.paused) drawPause();
	}
}
