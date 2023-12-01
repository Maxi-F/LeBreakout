#include "window.h"


#include "constants.h"

namespace LeBreakout {
	namespace Window {
		extern float deltaTime = 0;

		Vectors::Vector2 getMousePosition(sf::RenderWindow& window) {
			sf::Vector2i globalMousePosition = sf::Mouse::getPosition(window);
			return {
				(globalMousePosition.x * Constants::SCREEN_DIMENSIONS.x) / window.getViewport(window.getView()).width,
				(globalMousePosition.y * Constants::SCREEN_DIMENSIONS.y) / window.getViewport(window.getView()).height
			};
		}
	}
}
