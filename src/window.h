#pragma once
#include <SFML/Graphics.hpp>

#include "utils/Vector.h"

namespace LeBreakout {
	namespace Window {
		extern float deltaTime;

		Vectors::Vector2 getMousePosition(sf::RenderWindow& window);
	}
}
