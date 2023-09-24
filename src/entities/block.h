#pragma once
#include "utils/Rectangles.h"
#include "utils/Vector.h"
#include "entities/powerup.h"
#include "ball.h"

namespace Block {
	struct Block {
		Rectangles::Rectangle rectangle;
		PowerUps::PowerUp powerUp;
		bool hasBeenHit;
	};

	extern const double BLOCK_HEIGHT;
	extern const double BLOCK_WIDTH;

	void drawBlock(Block block);
	Block initBlock(Vectors::Vector2 position, PowerUps::PowerUp powerUp);
	void updateBlock(Block &block, Ball::Ball *ball);
}
