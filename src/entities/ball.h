#pragma once
#include "utils/Vector.h"
#include "utils/Rectangles.h"

namespace LeBreakout {
	namespace Ball {
		struct Ball {
			Vectors::Vector2 position;
			Vectors::Vector2 direction;
			Rectangles::Rectangle lastFrameCollisionBox;
			double velocity;
			double radius;
			bool hasBomb = false;
		};

		Ball initBall(Vectors::Vector2 position, Vectors::Vector2 direction);
	
		Rectangles::Rectangle getBallCollisionBox(Ball ball);
		void updateBall(Ball* ball, Rectangles::Rectangle paddleRectangle, bool& collidedBottom);
		void changeDirectionByCollisionPosition(Ball* ball, Rectangles::Rectangle blockRectangle);
	
		void drawBall(Ball* ball);
	}
}
