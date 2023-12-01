#pragma once
#include "utils/Rectangles.h"

namespace LeBreakout {
	namespace Paddle {
		struct Paddle {
			Rectangles::Rectangle rectangle;
			double velocity;
		};

		Paddle initPaddle();
		void drawPaddle(sf::RenderWindow& window, Paddle paddle);
		void updatePaddle(Paddle& paddle);
		void enlarge(Paddle& paddle);
		void reduce(Paddle& paddle);
		void reset(Paddle& paddle);
	}
}
