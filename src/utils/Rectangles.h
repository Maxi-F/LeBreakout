#pragma once
#include "Colors.h"

namespace Rectangles {
	struct Rectangle {
		double xCenter;
		double yCenter;
		double width;
		double height;
	};

	void fillRectangle(Rectangle rectangle, Colors::Color color);
	void outlineRectangle(Rectangle rectangle, Colors::Color color);
}