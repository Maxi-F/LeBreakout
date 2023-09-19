#pragma once
#include "Colors.h"

struct Rectangle {
	double xCenter;
	double yCenter;
	double width;
	double height;
};

void fillRectangle(Rectangle rectangle, Color color);
