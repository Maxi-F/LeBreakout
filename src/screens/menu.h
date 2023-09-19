#pragma once
#include "screens.h";

extern enum Option {
	PLAY = 0,
	GAME_RULES,
	GAME_CREDITS,
	EXIT,
	NONE
};

void initMenu();
void drawMenu();
Option getPressedOption();
void checkOptionCollisions();