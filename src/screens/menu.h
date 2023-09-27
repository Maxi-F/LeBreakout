#pragma once

#include "screens.h";

namespace LeBreakout {
	namespace Menu {
		enum Option {
			PLAY = 0,
			GAME_RULES,
			GAME_CREDITS,
			EXIT,
			NONE
		};

		void initMenu();
		void checkOptionCollisions(bool& isLeftClickPressed);
		void drawMenu();
		Option getPressedOption();
	}
}
