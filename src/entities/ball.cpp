#include "ball.h"

#include "sl.h"

#include "utils/Rectangles.h"
#include "utils/circles.h"
#include "utils/collisions.h"
#include "utils/math.h"
#include "constants.h"
#include "textureManager.h"


namespace LeBreakout {
	namespace Ball {
		static const double BALL_RADIUS = 10;
		static const double BALL_VELOCITY = 600;

		Ball initBall(Vectors::Vector2 position, Vectors::Vector2 direction) {
			return {
				position,
				direction,
				{},
				BALL_VELOCITY,
				BALL_RADIUS
			};
		}

		Rectangles::Rectangle getBallCollisionBox(Ball ball) {
			return {
				ball.position.x,
				ball.position.y,
				ball.radius * 2,
				ball.radius * 2
			};
		}
		static double getValuePerBallDirection(Ball ball, double directionPositiveValue, double directionNegativeValue) {
			return ball.direction.y > 0 ? directionPositiveValue : directionNegativeValue;
		}

		static double getDistancePercentageFromPaddle(Rectangles::Rectangle paddleRectangle, Ball& ball) {
			double distance = MathUtils::getDistanceFromMiddle(paddleRectangle, ball.position);
			double halfWidth = MathUtils::getHalf(paddleRectangle.width);

			return MathUtils::clamp(1 - (halfWidth - distance) / halfWidth, -1, 1) * 0.5;
		}

		static void checkPaddleCollision(Ball& ball, Rectangles::Rectangle paddleRectangle) {
			if (Collisions::checkRectangleCollision(getBallCollisionBox(ball), paddleRectangle)) {
				double directionPercentage = getDistancePercentageFromPaddle(paddleRectangle, ball);

				ball.direction = { directionPercentage, getValuePerBallDirection(ball, MathUtils::moduleOf(directionPercentage) - 1, 1 - MathUtils::moduleOf(directionPercentage)) };

				ball.position.y = paddleRectangle.yCenter + MathUtils::getHalf(paddleRectangle.height) + ball.radius;
			}
		}

		static void checkScreenCollision(Ball &ball, bool &collidedBottom) {
			if (ball.position.x - ball.radius < 0) {
				ball.position.x = ball.radius;
				ball.direction = { -ball.direction.x, ball.direction.y };
			}
			else if (ball.position.x + ball.radius > Constants::FIELD_DIMENSIONS.x) {
				ball.position.x = Constants::FIELD_DIMENSIONS.x - ball.radius;
				ball.direction = { -ball.direction.x, ball.direction.y };
			}

			if (ball.position.y + ball.radius > Constants::FIELD_DIMENSIONS.y) {
				ball.position.y = Constants::FIELD_DIMENSIONS.y - ball.radius;
				ball.direction = { ball.direction.x, -ball.direction.y };
			}
			else if (ball.position.y + ball.radius < 0) {
				collidedBottom = true;
			}
		}

		void updateBall(Ball *ball, Rectangles::Rectangle paddleRectangle, bool &collidedBottom) {
			checkPaddleCollision(*ball, paddleRectangle);
			checkScreenCollision(*ball, collidedBottom);

			ball->lastFrameCollisionBox = getBallCollisionBox(*ball);

			ball->position = {
				ball->position.x + ball->velocity * ball->direction.x * slGetDeltaTime(),
				ball->position.y + ball->velocity * ball->direction.y * slGetDeltaTime() 
			};
		}

		void changeDirectionByCollisionPosition(Ball* ball, Rectangles::Rectangle blockRectangle) {
			Collisions::CollisionPosition positionWhereCollided = Collisions::getCollisionPosition(
				ball->lastFrameCollisionBox,
				getBallCollisionBox(*ball),
				blockRectangle
			);

			switch (positionWhereCollided) {
				case Collisions::CollisionPosition::LEFT:
					ball->direction.x = -MathUtils::moduleOf(ball->direction.x);
					break;
				case Collisions::CollisionPosition::RIGHT:
					ball->direction.x = MathUtils::moduleOf(ball->direction.x);
					break;
				case Collisions::CollisionPosition::UP:
					ball->direction.y = -MathUtils::moduleOf(ball->direction.y);
					break;
				case Collisions::CollisionPosition::DOWN:
					ball->direction.y = MathUtils::moduleOf(ball->direction.y);
					break;
			}
		}

		void drawBall(Ball *ball) {
			Rectangles::Rectangle ballCollisionBox = getBallCollisionBox(*ball);
			const int SPRITE_ADDED_SIZE = 25;

			slSprite(
				TextureManager::obtainTexture(TextureManager::TextureType::BALL),
				ballCollisionBox.xCenter,
				ballCollisionBox.yCenter,
				ballCollisionBox.width + SPRITE_ADDED_SIZE,
				ballCollisionBox.height + SPRITE_ADDED_SIZE
			);
		}
	}
}
