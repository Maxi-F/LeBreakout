#pragma once
#include <vector>

#include "utils/vector.h"
#include "entities/paddle.h"
#include "entities/ball.h"

namespace PowerUps {
	enum PowerUpType {
		ADD_BALL = 0,
		ENLARGE,
		REDUCE,
		NONE
	};

	struct PowerUp {
		Vectors::Vector2 position;
		PowerUpType powerUpType;
		double radius;
		bool isFalling = false;
		bool collisioned = false;
	};

	extern const double POWER_UP_RADIUS;
	PowerUp createPowerUp(Vectors::Vector2 position);
	void drawPowerUp(PowerUp powerUp);
	void updatePowerUp(PowerUp& powerUp);
	void doPowerUp(PowerUp& powerUp, Paddle::Paddle& paddle, Ball::Ball& ball, std::vector<Ball::Ball>& balls);
}
