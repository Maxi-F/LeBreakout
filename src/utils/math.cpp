#include "Rectangles.h"
#include "Vector.h"
#include <stdlib.h>

namespace MathUtils {
	double getHalf(double value) {
		return value / 2.0;
	};

	double clamp(double value, double min, double max)
	{
		return (value < min) ? min : value > max ? max : value;
	}

	double getDistanceFromMiddle(Rectangles::Rectangle rectangle, Vectors::Vector2 point) {
		return point.x - rectangle.xCenter;
	}

	double moduleOf(double value) {
		return value < 0 ? -value : value;
	}

	int getRandomBetween(int min, int max) {
		return min + rand() % (max - min);
	}

	double positiveOrNegative() {
		return getRandomBetween(0, 2) == 0 ? -1 : 1;
	}
}
