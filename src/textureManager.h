#pragma once

namespace LeBreakout {
	namespace TextureManager {
		enum TextureType {
			MENU_BACKGROUND = 0,
			BUTTON,
			RULES_CREDITS_BACKGROUND,
			GAMEPLAY_BACKGROUND,
			PAUSE_BACKGROUND,
			BLOCK,
			PADDLE,
			BALL,
			ADD_BALL_POWER_UP,
			REDUCE_POWER_UP,
			ENLARGE_POWER_UP
		};

		void initTextureManager();
		int obtainTexture(TextureType texture);
	}
}
