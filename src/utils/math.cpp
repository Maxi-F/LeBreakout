#include "Rectangles.h"
#include "Vector.h"

double getHalf(double value) {
	return value / 2.0;
};

double clamp(double value, double min, double max)
{
	return (value < min) ? min : value > max ? max : value;
}

double getDistanceFromMiddle(Rectangle rectangle, Vector2 point) {
	return point.x - rectangle.xCenter;
}

double moduleOf(double value) {
	return value < 0 ? -value : value;
}
