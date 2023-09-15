#pragma once

struct Color {
	double r;
	double g;
	double b;
	double a;
};

extern const Color RED;
extern const Color LIGHT_BLUE;

void setBackColor(Color color);
void setForeColor(Color color);
