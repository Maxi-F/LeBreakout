#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace LeBreakout {
	namespace TextureManager {
		enum TextureType {
			MENU_BACKGROUND = 0,
			BUTTON,
			RULES_CREDITS_BACKGROUND,
			GAMEPLAY_BACKGROUND,
			PAUSE_BACKGROUND,
			BLOCK,
			PADDLE,
			BALL,
			ADD_BALL_POWER_UP,
			REDUCE_POWER_UP,
			ENLARGE_POWER_UP
		};

		void initTextureManager();
		sf::Texture obtainTexture(TextureType texture);
		void drawTexture(sf::RenderWindow& window, sf::Texture image, double x, double y, double width, double height);
		void unloadTextures();
	}
}
