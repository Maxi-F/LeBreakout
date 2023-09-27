#pragma once
#include "colors.h"

namespace LeBreakout {
	namespace Rectangles {
		struct Rectangle {
			double xCenter;
			double yCenter;
			double width;
			double height;
		};

		void fillRectangle(Rectangle rectangle, Colors::Color color);
	}
}