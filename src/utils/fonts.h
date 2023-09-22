#pragma once
#include "Colors.h"
#include "Vector.h"

namespace Fonts {
	void writeText(const char* text, Vectors::Vector2 position, Colors::Color color, int fontSize);
	void initFont(const char* filename);
	void setFontSize(int fontSize);
	Vectors::Vector2 getTextSize(const char* text);
}
