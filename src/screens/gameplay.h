#pragma once
#include "../entities/paddle.h"

struct GameplayEntities {
	Paddle paddle;
};

void updateGameplay();
void initGameplay();
void drawGameplay();
