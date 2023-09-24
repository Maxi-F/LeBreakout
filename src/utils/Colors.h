#pragma once

namespace Colors {
	struct Color {
		double r;
		double g;
		double b;
		double a;
	};

	extern const Color RED;
	extern const Color WHITE;
	extern const Color BLACK;
	extern const Color LIGHT_BLUE;
	extern const Color DARK_RED;
	extern const Color GRAY;
	extern const Color YELLOW;
	extern const Color PURPLE;
	extern const Color GREEN;

	void setBackColor(Color color);
	void setForeColor(Color color);
}
