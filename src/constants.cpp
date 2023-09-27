#include "constants.h"

#include "utils/vector.h"

namespace LeBreakout {
	namespace Constants {
		extern const Vectors::Vector2 SCREEN_DIMENSIONS = { 1920, 1080 };
		extern const double FIELD_Y_MARGIN = 80;
		extern const Vectors::Vector2 FIELD_DIMENSIONS = { Constants::SCREEN_DIMENSIONS.x, Constants::SCREEN_DIMENSIONS.y - FIELD_Y_MARGIN };
	}
}
