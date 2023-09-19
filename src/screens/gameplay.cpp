#include "gameplay.h"

GameplayEntities gameplayEntities;

void initGameplay() {
	Paddle paddle = initPaddle();

	gameplayEntities = { paddle };
}

void updateGameplay() {
	updatePaddle(gameplayEntities.paddle);
}

void drawGameplay() {
	drawPaddle(gameplayEntities.paddle);
}
