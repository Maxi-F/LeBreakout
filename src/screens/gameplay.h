#pragma once
#include "../entities/paddle.h"
#include "../entities/ball.h"
#include "../entities/block.h"

struct BallNode {
	Ball ball;
	BallNode* next;
};

struct BlockNode {
	Block block;
	BlockNode* next;
};

struct BlockRowNode {
	BlockNode* blockNode;
	BlockRowNode* next;
};

struct GameplayEntities {
	Paddle paddle;
	BallNode* balls;
	BlockRowNode* blockRows;
};

void updateGameplay();
void initGameplay();
void drawGameplay();
