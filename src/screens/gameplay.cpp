#include "gameplay.h"
#include "../utils/math.h"
#include "../constants.h"

namespace Gameplay {
	GameplayEntities gameplayEntities;

	static BlockRowNode* initBlockRows() {
		int blockRowsQuantity = MathUtils::getRandomBetween(3, 5);

		BlockRowNode* blockRows = new BlockRowNode();

		BlockRowNode* auxBlockRow = blockRows;
		for (int i = 0; i < blockRowsQuantity; i++) {
			auxBlockRow->blockNode = new BlockNode();

			int blocksInRowQuantity = MathUtils::getRandomBetween(4, 9);

			BlockNode* auxBlockNode = auxBlockRow->blockNode;

			double blockRowStartPosition = MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x) - (MathUtils::getHalf(blocksInRowQuantity) - 0.5) * Block::BLOCK_WIDTH;

			for (int j = 0; j < blocksInRowQuantity; j++) {
				auxBlockNode->block = Block::initBlock({
					blockRowStartPosition + j * Block::BLOCK_WIDTH,
					Constants::SCREEN_DIMENSIONS.y - Block::BLOCK_HEIGHT - i * Block::BLOCK_HEIGHT
					});
				auxBlockNode->next = new BlockNode();

				if (j + 1 < blocksInRowQuantity) {
					auxBlockNode = auxBlockNode->next;
				}
			}
			delete auxBlockNode->next;
			auxBlockNode->next = nullptr;

			auxBlockRow->next = new BlockRowNode();

			if (i + 1 < blockRowsQuantity) {
				auxBlockRow = auxBlockRow->next;
			}
		}

		delete auxBlockRow->next;
		auxBlockRow->next = nullptr;

		return blockRows;
	}

	void initGameplay() {
		Paddle::Paddle paddle = Paddle::initPaddle();
		BallNode* initBallNode = new BallNode({
			Ball::initBall({ MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x), MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y) }, { 0.5, 0.5 }),
			nullptr
			});

		int blockRowsQuantity = MathUtils::getRandomBetween(3, 5);

		BlockRowNode* blockRows = initBlockRows();

		gameplayEntities = { paddle, initBallNode, blockRows };
	}

	void updateGameplay() {
		updatePaddle(gameplayEntities.paddle);

		BallNode* initNode = gameplayEntities.balls;

		do {
			BlockRowNode* blockRow = gameplayEntities.blockRows;
			do {
				BlockNode* blockNode = blockRow->blockNode;

				do {
					updateBlock(blockNode->block, &initNode->ball);
					blockNode = blockNode->next;
				} while (blockNode != nullptr);

				blockRow = blockRow->next;
			} while (blockRow != nullptr);

			updateBall(&initNode->ball, gameplayEntities.paddle.rectangle);
			initNode = initNode->next;
		} while (initNode != nullptr);
	}

	void drawGameplay() {
		drawPaddle(gameplayEntities.paddle);

		BallNode* initNode = gameplayEntities.balls;

		do {
			drawBall(&initNode->ball);
			initNode = initNode->next;
		} while (initNode != nullptr);

		BlockRowNode* blockRow = gameplayEntities.blockRows;

		do {
			BlockNode* blockNode = blockRow->blockNode;

			do {
				drawBlock(blockNode->block);
				blockNode = blockNode->next;
			} while (blockNode != nullptr);

			blockRow = blockRow->next;
		} while (blockRow != nullptr);
	}
}
