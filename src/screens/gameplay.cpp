#include "gameplay.h"

#include <string>

#include "utils/math.h"
#include "constants.h"
#include "utils/Vector.h"
#include "utils/fonts.h"

namespace Gameplay {
	using Blocks = std::vector<std::vector<Block::Block>>;

	GameplayEntities gameplayEntities;

	static Blocks initBlockRows() {
		int blockRowsQuantity = MathUtils::getRandomBetween(3, 5);

		Blocks blocks(blockRowsQuantity, std::vector<Block::Block>(1));

		for (int i = 0; i < blockRowsQuantity; i++) {
			int blockColumnsQuantity = MathUtils::getRandomBetween(5, 9);
			double blockRowStartPosition = MathUtils::getHalf(Constants::FIELD_DIMENSIONS.x) - (MathUtils::getHalf(blockColumnsQuantity) - 0.5) * Block::BLOCK_WIDTH;
			
			blocks[i].resize(blockColumnsQuantity);

			for (int j = 0; j < blockColumnsQuantity; j++) {
				blocks[i][j] = Block::initBlock({
					blockRowStartPosition + j * Block::BLOCK_WIDTH,
					Constants::FIELD_DIMENSIONS.y - Block::BLOCK_HEIGHT - i * Block::BLOCK_HEIGHT
					});
			}
		}

		return blocks;
	}

	static Ball::Ball initBallInMiddle() {
		Vectors::Vector2 directions = { MathUtils::getHalf(MathUtils::positiveOrNegative()), MathUtils::getHalf(MathUtils::positiveOrNegative()) };
		return Ball::initBall({ MathUtils::getHalf(Constants::FIELD_DIMENSIONS.x), MathUtils::getHalf(Constants::FIELD_DIMENSIONS.y) }, directions);
	}

	void initGameplay() {
		Paddle::Paddle paddle = Paddle::initPaddle();
		std::vector<Ball::Ball> balls = { initBallInMiddle() };

		Blocks blocks = initBlockRows();

		Player::Player player = Player::initPlayer();

		gameplayEntities = { paddle, balls, blocks, player };
	}
	
	static void updateBlocks(Ball::Ball& ball) {
		for (int j = 0; j < gameplayEntities.blockRows.size(); j++) {
			for (int k = 0; k < gameplayEntities.blockRows[j].size(); k++) {
				Block::updateBlock(gameplayEntities.blockRows[j][k], &ball);
			}
		}
	}

	static void updateBallsAndBlocks() {
		for (int i = 0; i < gameplayEntities.balls.size(); i++) {
			updateBlocks(gameplayEntities.balls[i]);

			bool collidedBottom = false;
			Ball::updateBall(&gameplayEntities.balls[i], gameplayEntities.paddle.rectangle, collidedBottom);

			if (collidedBottom) {
				gameplayEntities.balls.erase(gameplayEntities.balls.begin() + i);

				if (gameplayEntities.balls.empty()) {
					Player::reduceLives(gameplayEntities.player);

					if (!Player::isStillAlive(gameplayEntities.player)) {
						gameplayEntities.hasLost = true;
					}

					gameplayEntities.balls.insert(gameplayEntities.balls.begin(), initBallInMiddle());
				}
			}
		}
	}

	static void updateGamplayEntities() {
		updatePaddle(gameplayEntities.paddle);
		updateBallsAndBlocks();
	}

	void updateGameplay(Screen::Screen &screen) {
		if (!gameplayEntities.hasWon && !gameplayEntities.hasLost) {
			updateGamplayEntities();
		}
		else {
			screen = Screen::MENU;
		}
	}

	static void drawUI() {
		Rectangles::Rectangle uiBackground = {
			MathUtils::getHalf(Constants::FIELD_DIMENSIONS.x),
			Constants::SCREEN_DIMENSIONS.y - MathUtils::getHalf(Constants::FIELD_Y_MARGIN),
			Constants::SCREEN_DIMENSIONS.x,
			Constants::FIELD_Y_MARGIN
		};

		Rectangles::fillRectangle(uiBackground, Colors::GRAY);

		const std::string livesPreText = "Lives: ";
		std::string lives = std::to_string(gameplayEntities.player.lives);
		std::string livesText = livesPreText + lives;

		Vectors::Vector2 livesTextSize = Fonts::getTextSize(livesText.c_str());

		double fontSize = 40;

		Fonts::writeText(
			livesText.c_str(),
			{ fontSize, Constants::FIELD_DIMENSIONS.y + MathUtils::getHalf(Constants::FIELD_Y_MARGIN) - MathUtils::getHalf(livesTextSize.y) },
			Colors::WHITE,
			fontSize
		);
	}

	void drawGameplay() {
		drawPaddle(gameplayEntities.paddle);

		for (int i = 0; i < gameplayEntities.balls.size(); i++) {
			Ball::drawBall(&gameplayEntities.balls[i]);
		}

		for (int i = 0; i < gameplayEntities.blockRows.size(); i++) {
			for (int j = 0; j < gameplayEntities.blockRows[i].size(); j++) {
				Block::drawBlock(gameplayEntities.blockRows[i][j]);
			}
		}

		drawUI();
	}
}
