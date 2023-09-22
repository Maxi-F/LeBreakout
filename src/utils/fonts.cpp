#include "sl.h"
#include "Colors.h"
#include "Vector.h"

namespace Fonts {
	static int ACTIVE_FONT;

	void initFont(const char* filename) {
		ACTIVE_FONT = slLoadFont(filename);
	};

	void setFontSize(int fontSize) {
		slSetFont(ACTIVE_FONT, fontSize);
	}

	void writeText(const char* text, Vectors::Vector2 position, Colors::Color color, int fontSize) {
		slSetForeColor(color.r, color.g, color.b, color.a);
		slSetFontSize(fontSize);
		slText(position.x, position.y, text);
	}
}
