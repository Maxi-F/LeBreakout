#include "gameplay_draws.h"

#include <string>

#include "sl.h"

#include "utils/Rectangles.h"
#include "utils/math.h"
#include "utils/vector.h"
#include "utils/fonts.h"
#include "utils/collisions.h"
#include "entities/paddle.h"
#include "entities/ball.h"
#include "entities/block.h"
#include "constants.h"
#include "textureManager.h"

namespace LeBreakout {
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
					MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
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
				default:
					return "";
			};
		}

		static void drawUI(Gameplay::GameplayEntities gameplayEntities) {
			Rectangles::Rectangle uiBackground = {
				MathUtils::getHalf(Constants::FIELD_DIMENSIONS.x),
				Constants::SCREEN_DIMENSIONS.y - MathUtils::getHalf(Constants::FIELD_Y_MARGIN),
				Constants::SCREEN_DIMENSIONS.x,
				Constants::FIELD_Y_MARGIN
			};

			Rectangles::fillRectangle(uiBackground, Colors::OPAQUE_DARK_RED);

			const std::string livesPreText = "Lives: ";
			std::string lives = std::to_string(gameplayEntities.player.lives);
			std::string livesText = livesPreText + lives;


			int fontSize = 55;

			Fonts::setFontSize(fontSize);

			Vectors::Vector2 livesTextSize = Fonts::getTextSize(livesText.c_str());

			Fonts::writeText(
				livesText.c_str(),
				{ static_cast<double>(fontSize), Constants::FIELD_DIMENSIONS.y + MathUtils::getHalf(Constants::FIELD_Y_MARGIN) - MathUtils::getHalf(livesTextSize.y) },
				Colors::WHITE,
				fontSize
			);

			const char* movementExplanation = "Press 'A' & 'D' to move.";
			Vectors::Vector2 movementTextSize = Fonts::getTextSize(movementExplanation);

			Fonts::writeText(
				movementExplanation,
				{
					MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x) - MathUtils::getHalf(movementTextSize.x),
					Constants::FIELD_DIMENSIONS.y + MathUtils::getHalf(Constants::FIELD_Y_MARGIN) - MathUtils::getHalf(movementTextSize.y)
				},
				Colors::WHITE,
				fontSize
			);

			const char* pauseExplanation = "Press 'ESC' to pause.";
			Vectors::Vector2 pauseTextSize = Fonts::getTextSize(pauseExplanation);

			Fonts::writeText(
				pauseExplanation,
				{
					Constants::SCREEN_DIMENSIONS.x - movementTextSize.x,
					Constants::FIELD_DIMENSIONS.y + MathUtils::getHalf(Constants::FIELD_Y_MARGIN) - MathUtils::getHalf(pauseTextSize.y)
				},
				Colors::WHITE,
				fontSize
			);
		}

		static void drawBox(const char* title, const GameplayMenuOption options[GAMEPLAY_MENU_OPTIONS_LENGTH]) {
			const Vectors::Vector2 MENU_SIZE = { 550, 700 };
			const Vectors::Vector2 mousePosition = { static_cast<double>(slGetMouseX()), static_cast<double>(slGetMouseY()) };

			Rectangles::Rectangle menu = {
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
				MENU_SIZE.x,
				MENU_SIZE.y
			};

			slSprite(
				TextureManager::obtainTexture(TextureManager::TextureType::PAUSE_BACKGROUND),
				menu.xCenter,
				menu.yCenter,
				menu.width,
				menu.height
			);
		
			int titleFontSize = 80;
			int titleMargin = 60;

			Fonts::setFontSize(titleFontSize);

			Vectors::Vector2 titleSize = Fonts::getTextSize(title);

			Fonts::writeText(
				title,
				{ 
					MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x) - MathUtils::getHalf(titleSize.x),
					MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y) + MathUtils::getHalf(MENU_SIZE.y) - titleSize.y - titleMargin
				},
				Colors::LIGHT_GRAY,
				titleFontSize
			);

			Colors::setForeColor(Colors::WHITE);

			for (int i = 0; i < GAMEPLAY_MENU_OPTIONS_LENGTH; i++) {
				slSprite(
					TextureManager::obtainTexture(TextureManager::TextureType::BUTTON),
					options[i].rectangle.xCenter,
					options[i].rectangle.yCenter,
					options[i].rectangle.width,
					options[i].rectangle.height
				);

				if (Collisions::checkPointToRectangleCollision(options[i].rectangle, mousePosition)) {
					Rectangles::fillRectangle(options[i].rectangle, Colors::OPAQUE_GRAY);
				}

				const char* optionText = optionToString(options[i].option);

				int optionFontSize = 50;
				Fonts::setFontSize(optionFontSize);
				Vectors::Vector2 optionSize = Fonts::getTextSize(optionText);

				Fonts::writeText(
					optionText,
					{ 
						options[i].rectangle.xCenter - MathUtils::getHalf(optionSize.x),
						options[i].rectangle.yCenter - MathUtils::getHalf(optionSize.y)
					},
					Colors::LIGHT_GRAY,
					optionFontSize
				);

				Colors::setForeColor(Colors::WHITE);
			}
		}

		static void drawPause() {
			drawBox("PAUSED", PAUSE_OPTIONS);
		}

		static void drawWinBox() {
			drawBox("You won!", LOSE_OR_WIN_OPTIONS);
		}

		static void drawLoseBox() {
			drawBox("You lost...", LOSE_OR_WIN_OPTIONS);
		}

		void drawGameplay(Gameplay::GameplayEntities gameplayEntities) {
			slSprite(
				TextureManager::obtainTexture(TextureManager::TextureType::GAMEPLAY_BACKGROUND),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
				Constants::SCREEN_DIMENSIONS.x,
				Constants::SCREEN_DIMENSIONS.y
			);

			Rectangles::fillRectangle(
				{
					MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
					MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
					Constants::SCREEN_DIMENSIONS.x,
					Constants::SCREEN_DIMENSIONS.y
				},
				Colors::OPAQUE_GRAY
			);
		
			Colors::setForeColor(Colors::WHITE);

			Paddle::drawPaddle(gameplayEntities.paddle);

			for (int i = 0; i < static_cast<int>(gameplayEntities.balls.size()); i++) {
				Ball::drawBall(&gameplayEntities.balls[i]);
			}

			for (int i = 0; i < static_cast<int>(gameplayEntities.blockRows.size()); i++) {
				for (int j = 0; j < static_cast<int>(gameplayEntities.blockRows[i].size()); j++) {
					Block::drawBlock(gameplayEntities.blockRows[i][j]);
				}
			}

			// This is in another loop so it draws on top of the blocks
			for (int i = 0; i < static_cast<int>(gameplayEntities.blockRows.size()); i++) {
				for (int j = 0; j < static_cast<int>(gameplayEntities.blockRows[i].size()); j++) {
					PowerUps::drawPowerUp(gameplayEntities.blockRows[i][j].powerUp);
				}
			}

			drawUI(gameplayEntities);

			if (gameplayEntities.hasLost) drawLoseBox();
			if (gameplayEntities.hasWon) drawWinBox();
			if (gameplayEntities.paused) drawPause();
		}
	}
}
