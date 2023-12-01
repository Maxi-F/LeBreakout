#pragma once
#include "screens/screens.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace LeBreakout {
	namespace RulesScreen {
		void drawRules(sf::RenderWindow& window);
		void changeScreen(sf::RenderWindow& window, Screen::Screen& screen);
	}
}
