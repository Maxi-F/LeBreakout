#pragma once
#include "rectangles.h"
#include "vector.h"

namespace LeBreakout {
	namespace MathUtils {
		double getHalf(double value);
		double clamp(double value, double min, double max);
		double getDistanceFromMiddle(Rectangles::Rectangle rectangle, Vectors::Vector2 point);
		double moduleOf(double value);
		int getRandomBetween(int min, int max);
		double positiveOrNegative();
	}
}