#include "rectangles.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "colors.h"
#include "window.h"

namespace LeBreakout {
	namespace Rectangles {
		static void doWithRectangle(Rectangle rectangle, void (*slFunction)(double x, double y, double width, double height)) {
			slFunction(rectangle.xCenter, rectangle.yCenter, rectangle.width, rectangle.height);
		}

		void fillRectangle(sf::RenderWindow& window, Rectangle rectangle, Colors::Color color) {
			sf::RectangleShape rectangleToDraw(sf::Vector2f(rectangle.width, rectangle.height));
			rectangleToDraw.setPosition(sf::Vector2f(rectangle.xCenter - rectangle.width / 2, rectangle.yCenter - rectangle.height / 2));
			rectangleToDraw.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
			
			window.draw(rectangleToDraw);
		};
	}
}
