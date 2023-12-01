#pragma once
#include "screens/screens.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace LeBreakout {
	namespace CreditsScreen {
		void drawCredits(sf::RenderWindow& window);
		void changeScreen(Screen::Screen& screen);
	}
}
