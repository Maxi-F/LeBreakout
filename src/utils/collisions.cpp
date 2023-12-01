#include "collisions.h"

#include "math.h"

namespace LeBreakout {
    namespace Collisions {
        CollisionPosition getCollisionPosition(Rectangles::Rectangle oldRectangle, Rectangles::Rectangle rectangleColliding, Rectangles::Rectangle rectangleToCollide) {
            float oldRectangleLeftEdge = oldRectangle.xCenter - MathUtils::getHalf(oldRectangle.width);
            float oldRectangleRightEdge = oldRectangle.xCenter + MathUtils::getHalf(oldRectangle.width);
            float oldRectangleBottomEdge = oldRectangle.yCenter - MathUtils::getHalf(oldRectangle.height);
            float oldRectangleTopEdge = oldRectangle.yCenter + MathUtils::getHalf(oldRectangle.height);

            float rectangleCollidingLeftEdge = rectangleColliding.xCenter - MathUtils::getHalf(rectangleColliding.width);
            float rectangleCollidingRightEdge = rectangleColliding.xCenter + MathUtils::getHalf(rectangleColliding.width);
            float rectangleCollidingBottomEdge = rectangleColliding.yCenter - MathUtils::getHalf(rectangleColliding.height);
            float rectangleCollidingTopEdge = rectangleColliding.yCenter + MathUtils::getHalf(rectangleColliding.height);

            float rectangleToCollideLeftEdge = rectangleToCollide.xCenter - MathUtils::getHalf(rectangleToCollide.width);
            float rectangleToCollideRightEdge = rectangleToCollide.xCenter + MathUtils::getHalf(rectangleToCollide.width);
            float rectangleToCollideBottomEdge = rectangleToCollide.yCenter - MathUtils::getHalf(rectangleToCollide.height);
            float rectangleToCollideTopEdge = rectangleToCollide.yCenter + MathUtils::getHalf(rectangleToCollide.height);

            if (
                oldRectangleRightEdge < rectangleToCollideLeftEdge &&
                rectangleCollidingRightEdge >= rectangleToCollideLeftEdge
                ) {
                return CollisionPosition::LEFT;
            }
            else if (
                oldRectangleLeftEdge >= rectangleToCollideRightEdge &&
                rectangleCollidingLeftEdge < rectangleToCollideRightEdge
                ) {
                return CollisionPosition::RIGHT;
            }
            else if (
                oldRectangleBottomEdge > rectangleToCollideTopEdge &&
                rectangleCollidingBottomEdge <= rectangleToCollideTopEdge
                ) {
                return CollisionPosition::DOWN;
            }
            else if (
                oldRectangleTopEdge <= rectangleToCollideBottomEdge &&
                rectangleCollidingTopEdge > rectangleToCollideBottomEdge
                ) {
                return CollisionPosition::UP;
            }

            return CollisionPosition::NO_COLLISION;
        }

        bool checkRectangleCollision(Rectangles::Rectangle rectangle1, Rectangles::Rectangle rectangle2) {
            float rectangle1LeftEdge = rectangle1.xCenter - MathUtils::getHalf(rectangle1.width);
            float rectangle1RightEdge = rectangle1.xCenter + MathUtils::getHalf(rectangle1.width);

            float rectangle2LeftEdge = rectangle2.xCenter - MathUtils::getHalf(rectangle2.width);
            float rectangle2RightEdge = rectangle2.xCenter + MathUtils::getHalf(rectangle2.width);

            float rectangle1BottomEdge = rectangle1.yCenter - MathUtils::getHalf(rectangle1.height);
            float rectangle1TopEdge = rectangle1.yCenter + MathUtils::getHalf(rectangle1.height);

            float rectangle2BottomEdge = rectangle2.yCenter - MathUtils::getHalf(rectangle2.height);
            float rectangle2TopEdge = rectangle2.yCenter + MathUtils::getHalf(rectangle2.height);

            return rectangle1RightEdge >= rectangle2LeftEdge &&
                rectangle1LeftEdge <= rectangle2RightEdge &&
                rectangle1BottomEdge <= rectangle2TopEdge &&
                rectangle1TopEdge >= rectangle2BottomEdge;
        };

        bool checkPointToRectangleCollision(Rectangles::Rectangle rectangle, Vectors::Vector2 point) {
            float rectangleLeftEdge = rectangle.xCenter - MathUtils::getHalf(rectangle.width);
            float rectangleRightEdge = rectangle.xCenter + MathUtils::getHalf(rectangle.width);
            float rectangleTopEdge = rectangle.yCenter - MathUtils::getHalf(rectangle.height);
            float rectangleBottomEdge = rectangle.yCenter + MathUtils::getHalf(rectangle.height);

            return point.x >= rectangleLeftEdge &&
                point.x <= rectangleRightEdge &&
                point.y <= rectangleBottomEdge &&
                point.y >= rectangleTopEdge;
        }
    }
}
