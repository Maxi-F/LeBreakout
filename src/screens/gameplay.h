#pragma once
#include "../entities/paddle.h"
#include "../entities/ball.h"

struct BallNode {
	Ball ball;
	BallNode* next;
};

struct GameplayEntities {
	Paddle paddle;
	BallNode* balls;
};

void updateGameplay();
void initGameplay();
void drawGameplay();
