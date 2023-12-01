#include "paddle.h";

#include <SFML/Window/Keyboard.hpp>

#include "utils/math.h"
#include "utils/Vector.h"
#include "constants.h"
#include "window.h"
#include "textureManager.h"

namespace LeBreakout {
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
					Constants::SCREEN_DIMENSIONS.y - PADDLE_MARGIN_TO_BOTTOM,
					PADDLE_SIZE.x,
					PADDLE_SIZE.y
				},
				PADDLE_VELOCITY
			};
		}

		void drawPaddle(sf::RenderWindow& window, Paddle paddle) {
			const int SPRITE_ADDED_HEIGHT = 20;

			TextureManager::drawTexture(
				window,
				TextureManager::obtainTexture(TextureManager::TextureType::PADDLE),
				paddle.rectangle.xCenter,
				paddle.rectangle.yCenter,
				paddle.rectangle.width,
				paddle.rectangle.height + SPRITE_ADDED_HEIGHT
			);
		}

		static void moveLeftIfPressing(Paddle& paddle) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && getPaddleLeftSide(paddle) > 0) {
				paddle.rectangle.xCenter -= paddle.velocity * Window::deltaTime;
			}
		}

		static void moveRightIfPressing(Paddle& paddle) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && getPaddleRightSide(paddle) < Constants::SCREEN_DIMENSIONS.x) {
				paddle.rectangle.xCenter += paddle.velocity * Window::deltaTime;
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
}
