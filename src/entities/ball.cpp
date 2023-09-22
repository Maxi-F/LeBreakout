#include "sl.h"
#include "ball.h"
#include "../utils/Rectangles.h"
#include "../utils/circles.h"
#include "../utils/collisions.h"
#include "../utils/math.h"
#include "../constants.h"

static const double BALL_RADIUS = 10;
static const double BALL_VELOCITY = 600;

Ball initBall(Vector2 position, Vector2 direction) {
	return {
		position,
		direction,
		BALL_VELOCITY,
		BALL_RADIUS
	};
}

Rectangle getBallCollisionBox(Ball ball) {
	return {
		ball.position.x,
		ball.position.y,
		ball.radius * 2,
		ball.radius * 2
	};
}

static float getValuePerBallDirection(Ball ball, float directionPositiveValue, float directionNegativeValue) {
	return ball.direction.y > 0 ? directionPositiveValue : directionNegativeValue;
}

static float getDistancePercentageFromPaddle(Rectangle paddleRectangle, Ball& ball) {
	float distance = getDistanceFromMiddle(paddleRectangle, ball.position);
	float halfWidth = getHalf(paddleRectangle.width);

	return clamp(1 - (halfWidth - distance) / halfWidth, -1, 1) * 0.5;
}

static void checkPaddleCollision(Ball& ball, Rectangle paddleRectangle) {
	if (checkRectangleCollision(getBallCollisionBox(ball), paddleRectangle)) {
		double directionPercentage = getDistancePercentageFromPaddle(paddleRectangle, ball);

		ball.direction = { directionPercentage, getValuePerBallDirection(ball, moduleOf(directionPercentage) - 1, 1 - moduleOf(directionPercentage)) };

		ball.position.y = paddleRectangle.yCenter + getHalf(paddleRectangle.height) + ball.radius;
	}
}

static void checkScreenCollision(Ball &ball) {
	if (ball.position.x - ball.radius < 0) {
		ball.position.x = ball.radius;
		ball.direction = { -ball.direction.x, ball.direction.y };
	}
	else if (ball.position.x + ball.radius > SCREEN_DIMENSIONS.x) {
		ball.position.x = SCREEN_DIMENSIONS.x - ball.radius;
		ball.direction = { -ball.direction.x, ball.direction.y };
	}

	if (ball.position.y + ball.radius > SCREEN_DIMENSIONS.y) {
		ball.position.y = SCREEN_DIMENSIONS.y - ball.radius;
		ball.direction = { ball.direction.x, -ball.direction.y };
	}
}

float lastDeltaTime;

void updateBall(Ball *ball, Rectangle paddleRectangle) {
	checkPaddleCollision(*ball, paddleRectangle);
	checkScreenCollision(*ball);

	ball->position = {
		ball->position.x + ball->velocity * ball->direction.x * slGetDeltaTime(),
		ball->position.y + ball->velocity * ball->direction.y * slGetDeltaTime() 
	};

	lastDeltaTime = slGetDeltaTime();
}

void changeDirectionByCollisionPosition(Ball* ball, Rectangle blockRectangle) {
	CollisionPosition positionWhereCollided = getCollisionPosition(
		{
		ball->position.x - ball->velocity * ball->direction.x * lastDeltaTime,
		ball->position.y - ball->velocity * ball->direction.y * lastDeltaTime,
		ball->radius * 2,
		ball->radius * 2
		},
		getBallCollisionBox(*ball),
		blockRectangle
	);

	switch (positionWhereCollided) {
		case CollisionPosition::LEFT:
		case CollisionPosition::RIGHT:
			ball->direction.x *= -1;
			break;
		case CollisionPosition::UP:
		case CollisionPosition::DOWN:
			ball->direction.y *= -1;
			break;
	}
}

void drawBall(Ball *ball) {
	drawCircle(ball->position, ball->radius, WHITE);
}
