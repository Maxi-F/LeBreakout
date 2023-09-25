#include "powerup.h"

#include "sl.h"

#include "utils/math.h"
#include "utils/collisions.h"
#include "utils/circles.h"
#include "utils/Colors.h"
#include "textureManager.h"

namespace PowerUps {
	static const double POWER_UP_FALL_VELOCITY = 200;
	extern const double POWER_UP_RADIUS = 20;

	static PowerUpType getRandomPowerUp() {
		const double POWER_UP_PROBABLITY = 0.25;

		int randomNumbersQuantity = PowerUpType::NONE * (1 / POWER_UP_PROBABLITY);
		int randomNumber = MathUtils::getRandomBetween(0, randomNumbersQuantity);

		return randomNumber > static_cast<int>(PowerUpType::NONE) ? PowerUpType::NONE : static_cast<PowerUpType>(randomNumber);
	}

	static TextureManager::TextureType getTexturePerPowerUp(PowerUpType powerUpType) {
		switch (powerUpType) {
			case PowerUpType::ADD_BALL:
				return TextureManager::TextureType::ADD_BALL_POWER_UP;
			case PowerUpType::ENLARGE:
				return TextureManager::TextureType::ENLARGE_POWER_UP;
			case PowerUpType::REDUCE:
				return TextureManager::TextureType::REDUCE_POWER_UP;
		}
	}

	Rectangles::Rectangle getPowerUpCollisionBox(PowerUp powerUp) {
		return {
			powerUp.position.x,
			powerUp.position.y,
			powerUp.radius * 2,
			powerUp.radius * 2
		};
	}

	PowerUp createPowerUp(Vectors::Vector2 position) {
		return {
			position,
			getRandomPowerUp(),
			POWER_UP_RADIUS
		};
	}

	void drawPowerUp(PowerUp powerUp) {
		if (powerUp.powerUpType != PowerUpType::NONE && !powerUp.collisioned && powerUp.isFalling) {
			Rectangles::Rectangle powerUpCollisionBox = getPowerUpCollisionBox(powerUp);
			TextureManager::TextureType texture = getTexturePerPowerUp(powerUp.powerUpType);

			slSprite(
				TextureManager::obtainTexture(texture),
				powerUpCollisionBox.xCenter,
				powerUpCollisionBox.yCenter,
				powerUpCollisionBox.width + 25,
				powerUpCollisionBox.height + 25
			);
		}
	};

	void doPowerUp(PowerUp& powerUp, Paddle::Paddle& paddle, Ball::Ball& ball, std::vector<Ball::Ball>& balls) {
		if (powerUp.powerUpType == PowerUpType::NONE || powerUp.collisioned) return;

		if (Collisions::checkRectangleCollision(getPowerUpCollisionBox(powerUp), paddle.rectangle)) {
			powerUp.collisioned = true;

			switch (powerUp.powerUpType) {
			case PowerUpType::ADD_BALL:
				balls.push_back(Ball::initBall(ball.position, { -ball.direction.x, MathUtils::getHalf(MathUtils::positiveOrNegative()) }));
				break;
			case PowerUpType::ENLARGE:
				Paddle::enlarge(paddle);
				break;
			case PowerUpType::REDUCE:
				Paddle::reduce(paddle);
				break;
			}
		}
	}

	void updatePowerUp(PowerUp &powerUp) {
		if (powerUp.powerUpType == PowerUpType::NONE) return;

		if (powerUp.isFalling && !powerUp.collisioned) {
			powerUp.position.y -= POWER_UP_FALL_VELOCITY * slGetDeltaTime();
		}
	};
}
