#pragma once
#include "screens/gameplay.h"

namespace GameplayDraws {
	extern const int GAMEPLAY_MENU_OPTIONS_LENGTH;

	enum GameplayOption {
		RESUME = 0,
		GO_TO_MENU,
		PLAY_AGAIN,
		NONE
	};

	struct GameplayMenuOption {
		Rectangles::Rectangle rectangle;
		GameplayOption option;
	};

	extern const GameplayMenuOption PAUSE_OPTIONS[];
	extern const GameplayMenuOption LOSE_OR_WIN_OPTIONS[];

	void drawGameplay(Gameplay::GameplayEntities gameplayEntities);
}
