#include "credits.h"

#include "sl.h"

#include "utils/math.h"
#include "utils/Rectangles.h"
#include "utils/collisions.h"
#include "utils/fonts.h"
#include "constants.h"
#include "textureManager.h"

namespace CreditsScreen {
	static const double MARGIN = 75;
	static const double GO_BACK_WIDTH = 300;
	static const double GO_BACK_HEIGHT = 100;

	static const Rectangles::Rectangle goBackRectangle = {
		MARGIN + MathUtils::getHalf(GO_BACK_WIDTH),
		MARGIN + MathUtils::getHalf(GO_BACK_HEIGHT),
		GO_BACK_WIDTH,
		GO_BACK_HEIGHT
	};


	void drawCredits() {
		int titleFontSize = 60;
		int textFontSize = 40;
		const int parts = 2;

		slSprite(
			TextureManager::obtainTexture(TextureManager::TextureType::RULES_CREDITS_BACKGROUND),
			MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
			MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
			Constants::SCREEN_DIMENSIONS.x,
			Constants::SCREEN_DIMENSIONS.y
		);

		Rectangles::fillRectangle(
			{
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.x),
				MathUtils::getHalf(Constants::SCREEN_DIMENSIONS.y),
				Constants::SCREEN_DIMENSIONS.x,
				Constants::SCREEN_DIMENSIONS.y
			},
			Colors::OPAQUE_GRAY
		);

		const char* artAssetsTitle = "Assets";
		const char* assetsText = "Kaden Ramstack";

		const char* developersTitle = "DEVELOPERS";
		const char* developerText = "Maximiliano Feldman";

		const char* titles[parts] = { developersTitle, artAssetsTitle };
		const char* texts[parts] = { developerText, assetsText };

		for (int i = 0; i < parts; i++) {
			Fonts::writeText(
				titles[i],
				{ MARGIN, Constants::SCREEN_DIMENSIONS.y - MARGIN * 2 - MARGIN * i * 2 },
				Colors::YELLOW,
				titleFontSize
			);

			Fonts::writeText(
				texts[i],
				{ MARGIN, Constants::SCREEN_DIMENSIONS.y - MARGIN * 3 - MARGIN * i * 2 },
				Colors::WHITE,
				titleFontSize
			);
		}

		int goBackFontSize = 60;
		
		Vectors::Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };

		slSprite(
			TextureManager::obtainTexture(TextureManager::TextureType::BUTTON),
			goBackRectangle.xCenter,
			goBackRectangle.yCenter,
			goBackRectangle.width,
			goBackRectangle.height
		);

		if (Collisions::checkPointToRectangleCollision(goBackRectangle, mousePosition)) {
			Rectangles::fillRectangle(
				goBackRectangle,
				Colors::OPAQUE_GRAY
			);
		}

		const char* goBackText = "Go back";
		Vectors::Vector2 goBackTextSize = Fonts::getTextSize(goBackText);

		Fonts::writeText(
			goBackText,
			{ goBackRectangle.xCenter - MathUtils::getHalf(goBackTextSize.x), goBackRectangle.yCenter - MathUtils::getHalf(goBackTextSize.y) },
			Colors::LIGHT_GRAY,
			goBackFontSize
		);

		Colors::setForeColor(Colors::WHITE);
	};

	void changeScreen(Screen::Screen& screen) {
		Vectors::Vector2 mousePosition = { slGetMouseX(), slGetMouseY() };

		if (Collisions::checkPointToRectangleCollision(goBackRectangle, mousePosition) && slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
			screen = Screen::MENU;
		}
	};
}
