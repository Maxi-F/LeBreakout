#pragma once
#include "colors.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace LeBreakout {
	namespace Rectangles {
		struct Rectangle {
			double xCenter;
			double yCenter;
			double width;
			double height;
		};

		void fillRectangle(sf::RenderWindow& window, Rectangle rectangle, Colors::Color color);
	}
}