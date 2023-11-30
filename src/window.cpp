#include "window.h"

#include "constants.h"

namespace LeBreakout {
	namespace Window {
		extern sf::RenderWindow window;
		extern float deltaTime = 0;

		void init() {
			window.create(sf::VideoMode(Constants::SCREEN_DIMENSIONS.x, Constants::SCREEN_DIMENSIONS.y), "LeBreakout");
		}
	}
}
