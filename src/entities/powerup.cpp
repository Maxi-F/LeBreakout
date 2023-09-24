#include "powerup.h"

#include "sl.h"

#include "utils/math.h"
#include "utils/collisions.h"
#include "utils/circles.h"
#include "utils/Colors.h"

static const double POWER_UP_FALL_VELOCITY = 200;

namespace PowerUps {
	static PowerUpType getRandomPowerUp() {
		const double POWER_UP_PROBABLITY = 0.25;

		int randomNumbersQuantity = PowerUpType::NONE * (1 / POWER_UP_PROBABLITY);
		int randomNumber = MathUtils::getRandomBetween(0, randomNumbersQuantity);

		return randomNumber > static_cast<int>(PowerUpType::NONE) ? PowerUpType::NONE : static_cast<PowerUpType>(randomNumber);
	}

	static Colors::Color getColorPerPowerUp(PowerUpType powerUpType) {
		switch (powerUpType) {
			case PowerUpType::ADD_BALL:
				return Colors::YELLOW;
			case PowerUpType::ENLARGE:
				return Colors::GREEN;
			case PowerUpType::REDUCE:
				return Colors::DARK_RED;
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
			20
		};
	}

	void drawPowerUp(PowerUp powerUp) {
		if (powerUp.powerUpType != PowerUpType::NONE && !powerUp.collisioned && powerUp.isFalling) {
			Circles::drawCircle(powerUp.position, powerUp.radius, getColorPerPowerUp(powerUp.powerUpType));
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
