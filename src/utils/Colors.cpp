#include "sl.h"
#include "Colors.h"

extern const Color RED = { 1, 0, 0, 1 };
extern const Color LIGHT_BLUE = { 0.5, 0.75, 1, 0 };

void setBackColor(Color color) {
	slSetBackColor(color.r, color.g, color.b);
}

void setForeColor(Color color) {
	slSetForeColor(color.r, color.g, color.b, color.a);
}
