#pragma once

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

void setBackColor(Color color);
void setForeColor(Color color);
