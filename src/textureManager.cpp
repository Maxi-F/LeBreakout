#include "textureManager.h"

#include <vector>
#include "sl.h"

namespace TextureManager {
	static struct Texture {
		int loadedTexture;
		TextureType textureType;
	};

	std::vector<Texture> textures;

	void initTextureManager() {
		Texture mainBackgroundTexture = { slLoadTexture("assets/morningCafe.png"), TextureType::MENU_BACKGROUND };
		Texture gameplayBackgroundTexture = { slLoadTexture("assets/nightCafe.png"), TextureType::GAMEPLAY_BACKGROUND };
		Texture creditsAndRulesBackgroundTexture = { slLoadTexture("assets/eveningCafe.png"), TextureType::RULES_CREDITS_BACKGROUND };
		Texture buttonTexture = { slLoadTexture("assets/button.png"), TextureType::BUTTON };
		
		Texture ballTexture = { slLoadTexture("assets/biscuitSingle.png"), TextureType::BALL };
		Texture paddleTexture = { slLoadTexture("assets/biscuitTray.png"), TextureType::PADDLE };
		Texture blockTexture = { slLoadTexture("assets/opera.png"), TextureType::BLOCK };

		Texture addBallTexture = { slLoadTexture("assets/biscuitsTray.png"), TextureType::ADD_BALL_POWER_UP };
		Texture enlargeTexture = { slLoadTexture("assets/milk.png"), TextureType::ENLARGE_POWER_UP };
		Texture reduceTexture = { slLoadTexture("assets/salt.png"), TextureType::REDUCE_POWER_UP };

		Texture pauseBackgroundTexture = { slLoadTexture("assets/recipePages.png"), TextureType::PAUSE_BACKGROUND };

		textures = { 
			mainBackgroundTexture,
			buttonTexture,
			creditsAndRulesBackgroundTexture,
			gameplayBackgroundTexture,
			ballTexture,
			paddleTexture,
			blockTexture,
			pauseBackgroundTexture,
			addBallTexture,
			reduceTexture,
			enlargeTexture,
		};
	}

	int obtainTexture(TextureType texture) {
		for (int i = 0; i < textures.size(); i++) {
			if (texture == textures[i].textureType) {
				return textures[i].loadedTexture;
			}
		}
	};
}
