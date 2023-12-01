#pragma once
#include "colors.h"
#include "vector.h"
#include "window.h"

namespace LeBreakout {
	namespace Fonts {
		void initFont(const char* filename);
		void setFontSize(int fontSize);
		Vectors::Vector2 getTextSize(const char* text);
		void writeText(sf::RenderWindow& window, const char* text, Vectors::Vector2 position, Colors::Color color, int fontSize);
		void unloadFont();
	}
}
