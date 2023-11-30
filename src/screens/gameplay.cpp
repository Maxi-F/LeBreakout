#include "gameplay.h"

#include <string>
#include <SFML/Window/Keyboard.hpp>

#include "screens/draws/gameplay_draws.h"
#include <SFML/Window/Mouse.hpp>
#include "utils/math.h"
#include "constants.h"
#include "utils/Vector.h"
#include "utils/fonts.h"
#include "entities/powerup.h"
#include "utils/collisions.h"

namespace LeBreakout {
	namespace Gameplay {
		using Blocks = std::vector<std::vector<Block::Block>>;

		GameplayEntities gameplayEntities;

		static Blocks initBlockRows() {
			const int MIN_BLOCK_ROWS_QUANTITY = 3;
			const int MAX_BLOCK_ROWS_QUANTITY = 5;
			const int MIN_BLOCKS_PER_ROW_QUANTITY = 5;
			const int MAX_BLOCKS_PER_ROW_QUANTITY = 9;

			int blockRowsQuantity = MathUtils::getRandomBetween(MIN_BLOCK_ROWS_QUANTITY, MAX_BLOCK_ROWS_QUANTITY);

			Blocks blocks(blockRowsQuantity, std::vector<Block::Block>(1));

			for (int i = 0; i < blockRowsQuantity; i++) {
				int blockColumnsQuantity = MathUtils::getRandomBetween(MIN_BLOCKS_PER_ROW_QUANTITY, MAX_BLOCKS_PER_ROW_QUANTITY);
				double halfPosition = MathUtils::getHalf(blockColumnsQuantity) - 0.5;
				double blockRowStartPosition = MathUtils::getHalf(Constants::FIELD_DIMENSIONS.x) - halfPosition * Block::BLOCK_WIDTH;
			
				blocks[i].resize(blockColumnsQuantity);

				for (int j = 0; j < blockColumnsQuantity; j++) {
					Vectors::Vector2 blockPosition = {
						blockRowStartPosition + j * Block::BLOCK_WIDTH,
						Constants::FIELD_DIMENSIONS.y - Block::BLOCK_HEIGHT - i * Block::BLOCK_HEIGHT
					};

					blocks[i][j] = Block::initBlock(blockPosition, PowerUps::createPowerUp(blockPosition));
				}
			}

			return blocks;
		}

		static Ball::Ball initBallInMiddle() {
			double upDirection = 0.5;
			Vectors::Vector2 directions = { MathUtils::getHalf(MathUtils::positiveOrNegative()), upDirection };

			return Ball::initBall({ MathUtils::getHalf(Constants::FIELD_DIMENSIONS.x), MathUtils::getHalf(Constants::FIELD_DIMENSIONS.y) }, directions);
		}

		void initGameplay() {
			Paddle::Paddle paddle = Paddle::initPaddle();
			std::vector<Ball::Ball> balls = { initBallInMiddle() };

			Blocks blocks = initBlockRows();

			Player::Player player = Player::initPlayer();

			gameplayEntities = { paddle, balls, blocks, player };
		}
	
		static void updateAndCheckBlocks(Ball::Ball& ball) {
			bool hasWon = true;

			for (int j = 0; j < gameplayEntities.blockRows.size(); j++) {
				for (int k = 0; k < gameplayEntities.blockRows[j].size(); k++) {
					if (!gameplayEntities.blockRows[j][k].hasBeenHit) {
						hasWon = false;
					}
					Block::updateBlock(gameplayEntities.blockRows[j][k], &ball);
					PowerUps::doPowerUp(gameplayEntities.blockRows[j][k].powerUp, gameplayEntities.paddle, ball, gameplayEntities.balls);
				}
			}

			gameplayEntities.hasWon = hasWon;
		}

		static void updateBallsAndBlocks() {
			for (int i = 0; i < gameplayEntities.balls.size(); i++) {
				updateAndCheckBlocks(gameplayEntities.balls[i]);

				bool collidedBottom = false;
				Ball::updateBall(&gameplayEntities.balls[i], gameplayEntities.paddle.rectangle, collidedBottom);

				if (collidedBottom) {
					gameplayEntities.balls.erase(gameplayEntities.balls.begin() + i);

					if (gameplayEntities.balls.empty()) {
						Player::reduceLives(gameplayEntities.player);
						Paddle::reset(gameplayEntities.paddle);

						if (!Player::isStillAlive(gameplayEntities.player)) {
							gameplayEntities.hasLost = true;
						}

						gameplayEntities.balls.insert(gameplayEntities.balls.begin(), initBallInMiddle());
					}
				}
			}
		}

		static void updatePowerUps() {
			for (int j = 0; j < gameplayEntities.blockRows.size(); j++) {
				for (int k = 0; k < gameplayEntities.blockRows[j].size(); k++) {
					PowerUps::updatePowerUp(gameplayEntities.blockRows[j][k].powerUp);
				}
			}
		}

		static void updateGamplayEntities() {
			updatePaddle(gameplayEntities.paddle);
			updateBallsAndBlocks();
			updatePowerUps();
		}

		static void doByGameplayOption(Screen::Screen &screen, GameplayDraws::GameplayOption option, bool& isLeftClickPressed) {
			switch (option) {
				case GameplayDraws::GameplayOption::RESUME:
					gameplayEntities.paused = false;
					break;
				case GameplayDraws::GameplayOption::PLAY_AGAIN:
					initGameplay();
					break;
				case GameplayDraws::GameplayOption::GO_TO_MENU:
					screen = Screen::Screen::MENU;
					isLeftClickPressed = true;
					break;
			}
		}

		void updateGameplay(Screen::Screen &screen, bool& isLeftClickPressed) {
			sf::Vector2i globalMousePosition = sf::Mouse::getPosition();
			Vectors::Vector2 mousePosition = { globalMousePosition.x, globalMousePosition.y };

			if (gameplayEntities.hasLost || gameplayEntities.hasWon) {
				GameplayDraws::GameplayOption selectedOption = GameplayDraws::GameplayOption::NONE;

				for (int i = 0; i < GameplayDraws::GAMEPLAY_MENU_OPTIONS_LENGTH; i++) {
					if (Collisions::checkPointToRectangleCollision(GameplayDraws::LOSE_OR_WIN_OPTIONS[i].rectangle, mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
						selectedOption = GameplayDraws::LOSE_OR_WIN_OPTIONS[i].option;
					}
				}

				doByGameplayOption(screen, selectedOption, isLeftClickPressed);
			}
			else if (gameplayEntities.paused) {
				GameplayDraws::GameplayOption selectedOption = GameplayDraws::GameplayOption::NONE;

				for (int i = 0; i < GameplayDraws::GAMEPLAY_MENU_OPTIONS_LENGTH; i++) {
					if (Collisions::checkPointToRectangleCollision(GameplayDraws::PAUSE_OPTIONS[i].rectangle, mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
						selectedOption = GameplayDraws::PAUSE_OPTIONS[i].option;
					}
				}

				doByGameplayOption(screen, selectedOption, isLeftClickPressed);
			}
			else {
				updateGamplayEntities();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					gameplayEntities.paused = true;
				}
			};
		}

		void drawGameplay() {
			GameplayDraws::drawGameplay(gameplayEntities);
		}
	}
}
