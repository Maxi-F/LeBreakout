#include "menu.h"

#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "textureManager.h"
#include "screens.h"
#include "constants.h"
#include "utils/collisions.h"
#include "utils/Rectangles.h"
#include "utils/Colors.h"
#include "utils/fonts.h"
#include "utils/math.h"
#include "utils/Vector.h"

namespace LeBreakout {
	namespace Menu {
		static const int MENU_OPTIONS_LENGTH = 4;

		struct MenuOption {
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
				HALF_SCREEN.y - OPTION_HEIGHT * 2 - OPTION_MARGIN * 2,
				OPTION_WIDTH,
				OPTION_HEIGHT
			};

			Rectangles::Rectangle rulesRectangle = {
				HALF_SCREEN.x,
				HALF_SCREEN.y - OPTION_HEIGHT - OPTION_MARGIN,
				OPTION_WIDTH,
				OPTION_HEIGHT
			};

			Rectangles::Rectangle creditsRectangle = {
				HALF_SCREEN.x,
				HALF_SCREEN.y ,
				OPTION_WIDTH,
				OPTION_HEIGHT
			};

			Rectangles::Rectangle exitRectangle = {
				HALF_SCREEN.x,
				HALF_SCREEN.y + OPTION_HEIGHT + OPTION_MARGIN,
				OPTION_WIDTH,
				OPTION_HEIGHT
			};

			MenuOption newMenuOptions[MENU_OPTIONS_LENGTH] = {
				{
					Option::PLAY,
					playRectangle,
					"PLAY"
				},
				{
					Option::GAME_RULES,
					rulesRectangle,
					"RULES"
				},
				{
					Option::GAME_CREDITS,
					creditsRectangle,
					"CREDITS"
				},
				{
					Option::EXIT,
					exitRectangle,
					"EXIT"
				}
			};

			for (int i = 0; i < MENU_OPTIONS_LENGTH; i++) {
				menuOptions[i] = newMenuOptions[i];
			}
		}

		void checkOptionCollisions(sf::RenderWindow& window, bool& isLeftClickPressed) {
			Vectors::Vector2 mousePosition = Window::getMousePosition(window);

			std::cout << "MOUSE: " << mousePosition.x << ", " << mousePosition.y << std::endl;

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				isLeftClickPressed = false;
			}

			for (int i = 0; i < MENU_OPTIONS_LENGTH; i++) {
				if (Collisions::checkPointToRectangleCollision(menuOptions[i].rectangle, mousePosition)) {
					menuOptions[i].isHovered = true;

					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isLeftClickPressed) {
						menuOptions[i].isClicked = true;
					}
				}
				else {
					menuOptions[i].isHovered = false;
				}
			}
		}

		void drawMenu(sf::RenderWindow& window) {
			TextureManager::drawTexture(
				window,
				TextureManager::obtainTexture(TextureManager::TextureType::MENU_BACKGROUND),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
				Constants::SCREEN_DIMENSIONS.x,
				Constants::SCREEN_DIMENSIONS.y
			);

			const char* title = "LeBreakout";
			int titleFontSize = 160;
			double titleMargin = 50;

			Fonts::setFontSize(titleFontSize);

			Vectors::Vector2 titleSize = Fonts::getTextSize(title);

			Fonts::writeText(
				window,
				title,
				{ HALF_SCREEN.x - MathUtils::getHalf(titleSize.x), titleMargin },
				Colors::BLACK,
				titleFontSize
			);

			for (int i = 0; i < MENU_OPTIONS_LENGTH; i++) {
				Fonts::setFontSize(OPTION_FONT_SIZE);
				const char* optionText = menuOptions[i].optionText;
				Rectangles::Rectangle optionRectangle = menuOptions[i].rectangle;

#ifdef _DEBUG
				Rectangles::fillRectangle(
					window,
					optionRectangle,
					Colors::RED
				);
#endif

				TextureManager::drawTexture(
					window,
					TextureManager::obtainTexture(TextureManager::TextureType::BUTTON),
					optionRectangle.xCenter,
					optionRectangle.yCenter,
					optionRectangle.width,
					optionRectangle.height
				);

				if (menuOptions[i].isHovered) {
					Rectangles::fillRectangle(window, menuOptions[i].rectangle, Colors::OPAQUE_GRAY);
				}

				Vectors::Vector2 optionTextSize = Fonts::getTextSize(optionText);
				Fonts::writeText(
					window,
					optionText,
					{ 
						optionRectangle.xCenter - MathUtils::getHalf(optionTextSize.x),
						optionRectangle.yCenter - MathUtils::getHalf(optionTextSize.y)
					},
					Colors::LIGHT_GRAY,
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
}
