#pragma once
#include "Rectangles.h"
#include "Vector.h"

namespace MathUtils {
	double getHalf(double value);
	double clamp(double value, double min, double max);
	double getDistanceFromMiddle(Rectangles::Rectangle rectangle, Vectors::Vector2 point);
	double moduleOf(double value);
	int getRandomBetween(int min, int max);
}