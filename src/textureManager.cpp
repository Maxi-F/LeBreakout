#include "textureManager.h"

#include <vector>
#include "window.h"

namespace LeBreakout {
	namespace TextureManager {
		static struct Texture {
			sf::Texture loadedTexture;
			TextureType textureType;
		};

		std::vector<Texture> textures;

		static sf::Texture createImage(const char* fileName) {
			sf::Texture image;
			image.loadFromFile(fileName);
			return image;
		}

		void initTextureManager() {
			Texture mainBackgroundTexture = { createImage("assets/morningCafe.png"), TextureType::MENU_BACKGROUND };
			Texture gameplayBackgroundTexture = { createImage("assets/nightCafe.png"), TextureType::GAMEPLAY_BACKGROUND };
			Texture creditsAndRulesBackgroundTexture = { createImage("assets/eveningCafe.png"), TextureType::RULES_CREDITS_BACKGROUND };
			Texture buttonTexture = { createImage("assets/button.png"), TextureType::BUTTON };
		
			Texture ballTexture = { createImage("assets/biscuitSingle.png"), TextureType::BALL };
			Texture paddleTexture = { createImage("assets/biscuitTray.png"), TextureType::PADDLE };
			Texture blockTexture = { createImage("assets/opera.png"), TextureType::BLOCK };

			Texture addBallTexture = { createImage("assets/biscuitsTray.png"), TextureType::ADD_BALL_POWER_UP };
			Texture enlargeTexture = { createImage("assets/milk.png"), TextureType::ENLARGE_POWER_UP };
			Texture reduceTexture = { createImage("assets/salt.png"), TextureType::REDUCE_POWER_UP };

			Texture pauseBackgroundTexture = { createImage("assets/recipePages.png"), TextureType::PAUSE_BACKGROUND };

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

		sf::Texture obtainTexture(TextureType texture) {
			for (int i = 0; i < textures.size(); i++) {
				if (texture == textures[i].textureType) {
					return textures[i].loadedTexture;
				}
			}
		};

		void drawTexture(sf::Texture image, double x, double y, double width, double height, sf::RenderWindow window) {
			sf::Sprite sprite;
			sprite.setTexture(image);
			sprite.setPosition(sf::Vector2f(x, y));
			sprite.setScale(sf::Vector2f(width / image.getSize().x, height / image.getSize().y));

			window.draw(sprite);
		}
	}
}
