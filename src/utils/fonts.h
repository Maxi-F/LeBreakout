#pragma once
#include "colors.h"
#include "vector.h"
#include <window.cpp>

namespace LeBreakout {
	namespace Fonts {
		void initFont(const char* filename);
		void setFontSize(int fontSize);
		Vectors::Vector2 getTextSize(const char* text);
		void writeText(const char* text, Vectors::Vector2 position, Colors::Color color, int fontSize, sf::RenderWindow window);
	}
}
