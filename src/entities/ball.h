#pragma once
#include "../utils/Vector.h"
#include "../utils/Rectangles.h"

struct Ball {
	Vector2 position;
	Vector2 direction;
	double velocity;
	double radius;
};

void drawBall(Ball* ball);
void updateBall(Ball* ball, Rectangle paddleRectangle);
void changeDirectionByCollisionPosition(Ball* ball, Rectangle blockRectangle);
Ball initBall(Vector2 position, Vector2 direction);
Rectangle getBallCollisionBox(Ball ball);
