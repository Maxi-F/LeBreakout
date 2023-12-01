#include "rules.h"

#include <SFML/Window/Mouse.hpp>

#include "utils/fonts.h"
#include "utils/circles.h"
#include "entities/powerup.h"
#include "constants.h"
#include "utils/math.h"
#include "utils/Rectangles.h"
#include "utils/collisions.h"
#include "textureManager.h"

namespace LeBreakout {
	namespace RulesScreen {
		static const double MARGIN = 100;
		static const double GO_BACK_WIDTH = 300;
		static const double GO_BACK_HEIGHT = 100;

		static const Rectangles::Rectangle goBackRectangle = {
			MARGIN + MathUtils::getHalf(GO_BACK_WIDTH),
			Constants::SCREEN_DIMENSIONS.y - MARGIN - MathUtils::getHalf(GO_BACK_HEIGHT),
			GO_BACK_WIDTH,
			GO_BACK_HEIGHT
		};

		static struct PowerUpWithText {
			TextureManager::TextureType texture;
			const char* text;
		};

		void drawRules(sf::RenderWindow& window) {
			const int FONT_SIZE = 60;

			TextureManager::drawTexture(
				window,
				TextureManager::obtainTexture(TextureManager::TextureType::RULES_CREDITS_BACKGROUND),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
				Constants::SCREEN_DIMENSIONS.x,
				Constants::SCREEN_DIMENSIONS.y
			);

			Rectangles::fillRectangle(
				window,
				{ 
					MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
					MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
					Constants::SCREEN_DIMENSIONS.x,
					Constants::SCREEN_DIMENSIONS.y
				},
				Colors::OPAQUE_GRAY
			);

			Fonts::setFontSize(FONT_SIZE);

			const int FIRST_TEXTS_COUNT = 3;
			const char* movementText = "Move with A and D. Pause with 'ESC' key.";
			const char* objectiveText = "Your objective is to break all blocks. When you break all blocks, you win!";
			const char* powerUpsTitle = "POWER UPS:";
	
			const char* firstTexts[] = {
				movementText,
				objectiveText,
				powerUpsTitle
			};

			for (int i = 0; i < FIRST_TEXTS_COUNT; i++) {
				Fonts::writeText(
					window,
					firstTexts[i],
					{ MARGIN, MARGIN + MARGIN * i },
					Colors::WHITE,
					FONT_SIZE
				);
			}

			const PowerUpWithText enlargeText = { TextureManager::TextureType::ENLARGE_POWER_UP, "Makes your scons (and consequentially your paddle!) bigger." };
			const PowerUpWithText reduceText = { TextureManager::TextureType::REDUCE_POWER_UP, "Makes your scons tastier, but takes the water away from your scons. your paddle gets smaller." };
			const PowerUpWithText addBallText = { TextureManager::TextureType::ADD_BALL_POWER_UP, "Adds a biscuit!" };

			const int POWER_UP_TEXTS_COUNT = 3;
			const PowerUpWithText powerUpTexts[POWER_UP_TEXTS_COUNT] = {
				enlargeText,
				reduceText,
				addBallText
			};

			for (int i = 0; i < POWER_UP_TEXTS_COUNT; i++) {
				Rectangles::Rectangle powerUpBox = PowerUps::getPowerUpCollisionBox({
						{
							MARGIN + PowerUps::POWER_UP_RADIUS,
							FIRST_TEXTS_COUNT * MARGIN + MARGIN * (i + 1) + PowerUps::POWER_UP_RADIUS
						},
						{},
						PowerUps::POWER_UP_RADIUS 
					});

				const int ADDED_SPRITE_SIZE = 40;

				TextureManager::drawTexture(
					window,
					TextureManager::obtainTexture(powerUpTexts[i].texture),
					powerUpBox.xCenter,
					powerUpBox.yCenter,
					powerUpBox.width + ADDED_SPRITE_SIZE,
					powerUpBox.height + ADDED_SPRITE_SIZE
				);

				Fonts::writeText(
					window,
					powerUpTexts[i].text,
					{
						MARGIN + PowerUps::POWER_UP_RADIUS * 3,
						FIRST_TEXTS_COUNT * MARGIN + MARGIN + MARGIN * i
					},
					Colors::WHITE,
					FONT_SIZE
				);
			}

			const char* randomlyGeneratedText = "All levels are randomly generated!";

			Fonts::writeText(
				window,
				randomlyGeneratedText,
				{
					MARGIN,
					(FIRST_TEXTS_COUNT + POWER_UP_TEXTS_COUNT) * MARGIN + MARGIN
				},
				Colors::WHITE,
				FONT_SIZE
			);

			Vectors::Vector2 mousePosition = Window::getMousePosition(window);

			TextureManager::drawTexture(
				window,
				TextureManager::obtainTexture(TextureManager::TextureType::BUTTON),
				goBackRectangle.xCenter,
				goBackRectangle.yCenter,
				goBackRectangle.width,
				goBackRectangle.height
			);

			if (Collisions::checkPointToRectangleCollision(goBackRectangle, mousePosition)) {
				Rectangles::fillRectangle(
					window,
					goBackRectangle,
					Colors::OPAQUE_GRAY
				);
			}

			const char* goBackText = "Go back";
			Vectors::Vector2 goBackTextSize = Fonts::getTextSize(goBackText);

			Fonts::writeText(
				window,
				goBackText,
				{ goBackRectangle.xCenter - MathUtils::getHalf(goBackTextSize.x), goBackRectangle.yCenter - MathUtils::getHalf(goBackTextSize.y) },
				Colors::LIGHT_GRAY,
				FONT_SIZE
			);

		}

		void changeScreen(sf::RenderWindow& window, Screen::Screen& screen) {
			Vectors::Vector2 mousePosition = Window::getMousePosition(window);

			if (Collisions::checkPointToRectangleCollision(goBackRectangle, mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				screen = Screen::MENU;
			}
		};
	}
}
