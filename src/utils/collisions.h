#pragma once

#include "Rectangles.h"
#include "Vector.h"

namespace Collisions {
	enum CollisionPosition {
		UP = 0,
		DOWN,
		RIGHT,
		LEFT,
		NO_COLLISION
	};

	CollisionPosition getCollisionPosition(Rectangles::Rectangle oldRectangle, Rectangles::Rectangle rectangleColliding, Rectangles::Rectangle rectangleToCollide);
	bool checkRectangleCollision(Rectangles::Rectangle rectangle1, Rectangles::Rectangle rectangle2);
	bool checkPointToRectangleCollision(Rectangles::Rectangle rectangle, Vectors::Vector2 point);
}
