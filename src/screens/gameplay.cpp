#include "gameplay.h"
#include "../utils/math.h"
#include "../constants.h"

GameplayEntities gameplayEntities;

void initGameplay() {
	Paddle paddle = initPaddle();
	BallNode* initBallNode = new BallNode({
		initBall({ getHalf(SCREEN_DIMENSIONS.x), getHalf(SCREEN_DIMENSIONS.y) }, { 0.5, 0.5 }),
		nullptr
		});

	gameplayEntities = { paddle, initBallNode };
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
}
