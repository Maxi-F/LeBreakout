#include "sl.h"
#include "Colors.h"

namespace Colors {
	extern const Color RED = { 1, 0, 0, 1 };
	extern const Color LIGHT_BLUE = { 0.5, 0.75, 1, 1 };
	extern const Color BLACK = { 0, 0, 0, 1 };
	extern const Color WHITE = { 1, 1, 1, 1 };
	extern const Color DARK_RED = { 0.6, 0, 0, 1 };
	extern const Color GRAY = { 0.612, 0.612, 0.612, 1 };
	extern const Color YELLOW = { 1, 1, 0, 1 };
	extern const Color PURPLE = { 1, 0, 1, 1 };
	extern const Color GREEN = { 0, 1, 0, 1 };

	void setBackColor(Color color) {
		slSetBackColor(color.r, color.g, color.b);
	}

	void setForeColor(Color color) {
		slSetForeColor(color.r, color.g, color.b, color.a);
	}
}
