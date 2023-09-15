#include "Rectangles.h"
#include "sl.h"

static void doWithRectangle(Rectangle rectangle, void (*slFunction)(double x, double y, double width, double height)) {
	slFunction(rectangle.xCenter, rectangle.yCenter, rectangle.width, rectangle.height);
}

void fillRectangle(Rectangle rectangle) {
	doWithRectangle(rectangle, slRectangleFill);
};
