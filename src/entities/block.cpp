#include "block.h"

extern const double BLOCK_HEIGHT = 60;
extern const double BLOCK_WIDTH = 150;

Block initBlock(Vector2 position) {
	return {
		{ position.x, position.y, BLOCK_WIDTH, BLOCK_HEIGHT },
		false
	};
}

void drawBlock(Block block) {
	if (!block.hasBeenHit) {
		fillRectangle(block.rectangle, LIGHT_BLUE);
		outlineRectangle(block.rectangle, DARK_RED);
	}
}

void updateBlock(Block& block) {};
