#include "sl.h"
#include "paddle.h";
#include "utils/math.h"
#include "utils/Vector.h"
#include "constants.h"

namespace Paddle {
	extern const Vectors::Vector2 PADDLE_SIZE = { 150, 30 };
	extern const double PADDLE_VELOCITY = 500;
	static const double PADDLE_MARGIN_TO_BOTTOM = 100;
	static const double PADDLE_ENLARGE_AND_REDUCE_WIDTH = 50;
	static const double PADDLE_MIN_WIDTH = 50;
	static const double PADDLE_MAX_WIDTH = 350;

	static double getPaddleLeftSide(Paddle paddle) {
		return paddle.rectangle.xCenter - MathUtils::getHalf(paddle.rectangle.width);
	}

	static double getPaddleRightSide(Paddle paddle) {
		return paddle.rectangle.xCenter + MathUtils::getHalf(paddle.rectangle.width);
	}

	Paddle initPaddle() {
		return {
			{
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
				PADDLE_MARGIN_TO_BOTTOM,
				PADDLE_SIZE.x,
				PADDLE_SIZE.y
			},
			PADDLE_VELOCITY,
			Colors::RED
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
		if (slGetKey('D') && getPaddleRightSide(paddle) < Constants::SCREEN_DIMENSIONS.x) {
			paddle.rectangle.xCenter += paddle.velocity * slGetDeltaTime();
		}
	}

	void updatePaddle(Paddle& paddle) {
		moveLeftIfPressing(paddle);
		moveRightIfPressing(paddle);
	}

	void enlarge(Paddle& paddle) {
		paddle.rectangle.width = MathUtils::clamp(paddle.rectangle.width + PADDLE_ENLARGE_AND_REDUCE_WIDTH, PADDLE_MIN_WIDTH, PADDLE_MAX_WIDTH);
	}

	void reduce(Paddle& paddle) {
		paddle.rectangle.width = MathUtils::clamp(paddle.rectangle.width - PADDLE_ENLARGE_AND_REDUCE_WIDTH, PADDLE_MIN_WIDTH, PADDLE_MAX_WIDTH);
	}

	void reset(Paddle& paddle) {
		paddle.rectangle.width = PADDLE_SIZE.x;
	}
}
