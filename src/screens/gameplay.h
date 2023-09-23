#pragma once
#include <vector>

#include "screens/screens.h"
#include "entities/paddle.h"
#include "entities/ball.h"
#include "entities/block.h"
#include "entities/player.h"

namespace Gameplay {
	struct GameplayEntities {
		Paddle::Paddle paddle;
		std::vector<Ball::Ball> balls;
		std::vector<std::vector<Block::Block>> blockRows;
		Player::Player player;
		bool hasWon = false;
		bool hasLost = false;
	};

	void updateGameplay(Screen::Screen &screen);
	void initGameplay();
	void drawGameplay();
}
