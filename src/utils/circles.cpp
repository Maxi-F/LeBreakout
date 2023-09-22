#include "sl.h"
#include "Colors.h"
#include "Vector.h"

static const int NUM_VERTICES = 50;

void drawCircle(Vector2 center, double radius, Color color) {
	setForeColor(color);
	slCircleFill(center.x, center.y, radius, NUM_VERTICES);
}
