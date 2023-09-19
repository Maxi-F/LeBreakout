#pragma once

extern enum Option {
	PLAY = 0,
	GAME_RULES,
	CREDITS,
	EXIT,
	NONE
};

void initMenu();
void drawMenu();
Option getPressedOption();
