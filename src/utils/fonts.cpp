#include "fonts.h"

#include "sl.h"

#include "colors.h"
#include "vector.h"

namespace LeBreakout {
	namespace Fonts {
		static int ACTIVE_FONT;

		void initFont(const char* filename) {
			ACTIVE_FONT = slLoadFont(filename);
		};

		void setFontSize(int fontSize) {
			slSetFont(ACTIVE_FONT, fontSize);
		}

		Vectors::Vector2 getTextSize(const char* text) {
			return { slGetTextWidth(text), slGetTextHeight(text) };
		}

		void writeText(const char* text, Vectors::Vector2 position, Colors::Color color, int fontSize) {
			slSetForeColor(color.r, color.g, color.b, color.a);
			slSetFontSize(fontSize);
			slText(position.x, position.y, text);
		}
	}
}
