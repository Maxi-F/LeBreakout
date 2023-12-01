#pragma once
#include <vector>

#include "utils/vector.h"
#include "entities/paddle.h"
#include "entities/ball.h"

namespace LeBreakout {
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
		Rectangles::Rectangle getPowerUpCollisionBox(PowerUp powerUp);

		PowerUp createPowerUp(Vectors::Vector2 position);
		void drawPowerUp(sf::RenderWindow& window, PowerUp powerUp);
		void doPowerUp(PowerUp& powerUp, Paddle::Paddle& paddle, Ball::Ball& ball, std::vector<Ball::Ball>& balls);
		void updatePowerUp(PowerUp& powerUp);
	}
}
