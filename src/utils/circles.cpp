#include "sl.h"
#include "Colors.h"
#include "Vector.h"

namespace Circles {
	static const int NUM_VERTICES = 50;

	void drawCircle(Vectors::Vector2 center, double radius, Colors::Color color) {
		setForeColor(color);
		slCircleFill(center.x, center.y, radius, NUM_VERTICES);
	}
}
