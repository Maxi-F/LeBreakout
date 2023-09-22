#include "gameplay.h"
#include "../utils/math.h"
#include "../constants.h"

GameplayEntities gameplayEntities;

static BlockRowNode* initBlockRows() {
	int blockRowsQuantity = getRandomBetween(3, 5);

	BlockRowNode* blockRows = new BlockRowNode();

	BlockRowNode* auxBlockRow = blockRows;
	for (int i = 0; i < blockRowsQuantity; i++) {
		auxBlockRow->blockNode = new BlockNode();

		int blocksInRowQuantity = getRandomBetween(4, 9);

		BlockNode* auxBlockNode = auxBlockRow->blockNode;
		 
		double blockRowStartPosition = getHalf(SCREEN_DIMENSIONS.x) - (getHalf(blocksInRowQuantity) - 0.5) * BLOCK_WIDTH;

		for (int j = 0; j < blocksInRowQuantity; j++) {
			auxBlockNode->block = initBlock({
				blockRowStartPosition + j * BLOCK_WIDTH,
				SCREEN_DIMENSIONS.y - BLOCK_HEIGHT - i * BLOCK_HEIGHT
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
	Paddle paddle = initPaddle();
	BallNode* initBallNode = new BallNode({
		initBall({ getHalf(SCREEN_DIMENSIONS.x), getHalf(SCREEN_DIMENSIONS.y) }, { 0.5, 0.5 }),
		nullptr
		});

	int blockRowsQuantity = getRandomBetween(3, 5);

	BlockRowNode* blockRows = initBlockRows();

	gameplayEntities = { paddle, initBallNode, blockRows };
}

void updateGameplay() {
	updatePaddle(gameplayEntities.paddle);

	BallNode* initNode = gameplayEntities.balls;

	do {
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
