#pragma once
#include "../utils/Rectangles.h"

struct Paddle {
	Rectangle rectangle;
	double velocity;
	Color color;
};

Paddle initPaddle();
void updatePaddle(Paddle& paddle);
void drawPaddle(Paddle paddle);