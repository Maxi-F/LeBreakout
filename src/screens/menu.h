#pragma once

#include "screens.h";
#include <SFML/Graphics/RenderWindow.hpp>

namespace LeBreakout {
	namespace Menu {
		enum Option {
			PLAY = 0,
			GAME_RULES,
			GAME_CREDITS,
			EXIT,
			NONE
		};

		void initMenu();
		void checkOptionCollisions(sf::RenderWindow& window, bool& isLeftClickPressed);
		void drawMenu(sf::RenderWindow& window);
		Option getPressedOption();
	}
}
