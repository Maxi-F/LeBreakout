#pragma once
#include "vector.h"
#include "colors.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace LeBreakout {
	namespace Circles {
		void drawCircle(sf::RenderWindow& window, Vectors::Vector2 center, double radius, Colors::Color color);
	}
}
