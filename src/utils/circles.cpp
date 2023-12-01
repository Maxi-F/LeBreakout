#include "circles.h"

#include <SFML/Graphics/CircleShape.hpp>

#include "Colors.h"
#include "Vector.h"
#include "window.h"

namespace LeBreakout {
	namespace Circles {
		static const int NUM_VERTICES = 50;

		void drawCircle(sf::RenderWindow& window, Vectors::Vector2 center, double radius, Colors::Color color) {
			sf::CircleShape circle = sf::CircleShape(radius);

			circle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
			circle.setPosition(sf::Vector2f(center.x - radius, center.y - radius));
			window.draw(circle);
		}
	}
}
