#pragma once
#include "../utils/Vector.h"
#include "../utils/Rectangles.h"

namespace Ball {
	struct Ball {
		Vectors::Vector2 position;
		Vectors::Vector2 direction;
		Rectangles::Rectangle lastFrameCollisionBox;
		double velocity;
		double radius;
	};

	void drawBall(Ball* ball);
	void updateBall(Ball* ball, Rectangles::Rectangle paddleRectangle, bool& collidedBottom);
	void changeDirectionByCollisionPosition(Ball* ball, Rectangles::Rectangle blockRectangle);
	Ball initBall(Vectors::Vector2 position, Vectors::Vector2 direction);
	Rectangles::Rectangle getBallCollisionBox(Ball ball);
}
