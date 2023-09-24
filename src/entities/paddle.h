#pragma once
#include "utils/Rectangles.h"

namespace Paddle {
	struct Paddle {
		Rectangles::Rectangle rectangle;
		double velocity;
		Colors::Color color;
	};

	Paddle initPaddle();
	void updatePaddle(Paddle& paddle);
	void drawPaddle(Paddle paddle);
	void enlarge(Paddle& paddle);
	void reduce(Paddle& paddle);
	void reset(Paddle& paddle);
}
