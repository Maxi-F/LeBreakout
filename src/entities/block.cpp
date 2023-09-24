#include "block.h"

#include "ball.h"
#include "utils/collisions.h"

namespace Block {
	extern const double BLOCK_HEIGHT = 60;
	extern const double BLOCK_WIDTH = 150;

	Block initBlock(Vectors::Vector2 position, PowerUps::PowerUp powerUp) {
		return {
			{ position.x, position.y, BLOCK_WIDTH, BLOCK_HEIGHT },
			powerUp,
			false
		};
	}

	void drawBlock(Block block) {
		if (!block.hasBeenHit) {
			Rectangles::fillRectangle(block.rectangle, Colors::LIGHT_BLUE);
			Rectangles::outlineRectangle(block.rectangle, Colors::DARK_RED);
		}
	}

	void updateBlock(Block& block, Ball::Ball *ball) {
		if (!block.hasBeenHit && Collisions::checkRectangleCollision(block.rectangle, getBallCollisionBox(*ball))) {
			changeDirectionByCollisionPosition(ball, block.rectangle);
			block.hasBeenHit = true;
			block.powerUp.isFalling = true;
		}
	};
}
