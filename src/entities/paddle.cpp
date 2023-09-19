#include "sl.h"
#include "paddle.h";
#include "../utils/math.h"
#include "../utils/Vector.h"
#include "../constants.h"

extern const Vector2 PADDLE_SIZE = { 360, 30 };
extern const float PADDLE_VELOCITY = 500;
static const float PADDLE_MARGIN_TO_BOTTOM = 200;

static double getPaddleLeftSide(Paddle paddle) {
	return paddle.rectangle.xCenter - getHalf(paddle.rectangle.width);
}

static double getPaddleRightSide(Paddle paddle) {
	return paddle.rectangle.xCenter + getHalf(paddle.rectangle.width);
}

Paddle initPaddle() {
	return {
		{ 
			getHalf(SCREEN_DIMENSIONS.x),
			PADDLE_MARGIN_TO_BOTTOM,
			PADDLE_SIZE.x,
			PADDLE_SIZE.y
		},
		PADDLE_VELOCITY,
		RED
	};
}

void drawPaddle(Paddle paddle) {
	fillRectangle(paddle.rectangle, paddle.color);
}

static void moveLeftIfPressing(Paddle& paddle) {
	if (slGetKey('A') && getPaddleLeftSide(paddle) > 0) {
		paddle.rectangle.xCenter -= paddle.velocity * slGetDeltaTime();
	}
}

static void moveRightIfPressing(Paddle& paddle) {
	if (slGetKey('D') && getPaddleRightSide(paddle) < SCREEN_DIMENSIONS.x) {
		paddle.rectangle.xCenter += paddle.velocity * slGetDeltaTime();
	}
}

void updatePaddle(Paddle& paddle) {
	moveLeftIfPressing(paddle);
	moveRightIfPressing(paddle);
}
