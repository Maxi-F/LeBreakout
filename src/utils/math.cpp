#include "math.h"

#include <stdlib.h>

#include "rectangles.h"
#include "vector.h"

namespace LeBreakout {
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
			return static_cast<int>(min + rand() % (max + 1 - min));
		}

		double positiveOrNegative() {
			return getRandomBetween(0, 1) == 0 ? -1 : 1;
		}
	}
}
