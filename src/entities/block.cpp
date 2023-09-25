#include "block.h"

#include "sl.h"

#include "ball.h"
#include "utils/collisions.h"
#include "textureManager.h"

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
			slSprite(
				TextureManager::obtainTexture(TextureManager::TextureType::BLOCK),
				block.rectangle.xCenter,
				block.rectangle.yCenter,
				block.rectangle.width + 60,
				block.rectangle.height + 40
			);
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
