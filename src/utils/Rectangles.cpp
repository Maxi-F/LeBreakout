#include "sl.h"

#include "Rectangles.h"
#include "Colors.h"

namespace Rectangles {
	static void doWithRectangle(Rectangle rectangle, void (*slFunction)(double x, double y, double width, double height)) {
		slFunction(rectangle.xCenter, rectangle.yCenter, rectangle.width, rectangle.height);
	}

	void fillRectangle(Rectangle rectangle, Colors::Color color) {
		setForeColor(color);
		doWithRectangle(rectangle, slRectangleFill);
	};

	void outlineRectangle(Rectangle rectangle, Colors::Color color) {
		setForeColor(color);
		doWithRectangle(rectangle, slRectangleOutline);
	}
}
