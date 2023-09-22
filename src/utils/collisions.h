#pragma once

#include "Rectangles.h"
#include "Vector.h"

extern enum CollisionPosition {
	UP = 0,
	DOWN,
	RIGHT,
	LEFT,
	NO_COLLISION
};

CollisionPosition getCollisionPosition(Rectangle oldRectangle, Rectangle rectangleColliding, Rectangle rectangleToCollide);
bool checkRectangleCollision(Rectangle rectangle1, Rectangle rectangle2);
bool checkPointToRectangleCollision(Rectangle rectangle, Vector2 point);
