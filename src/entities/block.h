#pragma once
#include "utils/Rectangles.h"
#include "utils/Vector.h"
#include "entities/powerup.h"
#include "ball.h"

namespace LeBreakout {
	namespace Block {
		struct Block {
			Rectangles::Rectangle rectangle;
			PowerUps::PowerUp powerUp;
			bool hasBeenHit;
		};

		extern const double BLOCK_HEIGHT;
		extern const double BLOCK_WIDTH;

		Block initBlock(Vectors::Vector2 position, PowerUps::PowerUp powerUp);
		void drawBlock(Block block);
		void updateBlock(Block &block, Ball::Ball *ball);
	}
}
