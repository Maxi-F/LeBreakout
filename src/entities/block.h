#pragma once
#include "../utils/Rectangles.h"
#include "../utils/Vector.h"
#include "ball.h"

struct Block {
	Rectangle rectangle;
	bool hasBeenHit;
};

extern const double BLOCK_HEIGHT;
extern const double BLOCK_WIDTH;

void drawBlock(Block block);
Block initBlock(Vector2 position);
void updateBlock(Block &block, Ball *ball);
