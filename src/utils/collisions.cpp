#include "collisions.h"
#include "math.h"

CollisionPosition getCollisionPosition(Rectangle oldRectangle, Rectangle rectangleColliding, Rectangle rectangleToCollide) {
    float oldRectangleLeftEdge = oldRectangle.xCenter - getHalf(oldRectangle.width);
    float oldRectangleRightEdge = oldRectangle.xCenter + getHalf(oldRectangle.width);
    float oldRectangleBottomEdge = oldRectangle.yCenter - getHalf(oldRectangle.height);
    float oldRectangleTopEdge = oldRectangle.yCenter + getHalf(oldRectangle.height);

    float rectangleCollidingLeftEdge = rectangleColliding.xCenter - getHalf(rectangleColliding.width);
    float rectangleCollidingRightEdge = rectangleColliding.xCenter + getHalf(rectangleColliding.width);
    float rectangleCollidingBottomEdge = rectangleColliding.yCenter - getHalf(rectangleColliding.height);
    float rectangleCollidingTopEdge = rectangleColliding.yCenter + getHalf(rectangleColliding.height);

    float rectangleToCollideLeftEdge = rectangleToCollide.xCenter - getHalf(rectangleToCollide.width);
    float rectangleToCollideRightEdge = rectangleToCollide.xCenter + getHalf(rectangleToCollide.width);
    float rectangleToCollideBottomEdge = rectangleToCollide.yCenter - getHalf(rectangleToCollide.height);
    float rectangleToCollideTopEdge = rectangleToCollide.yCenter + getHalf(rectangleToCollide.height);

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

bool checkRectangleCollision(Rectangle rectangle1, Rectangle rectangle2) {
    float rectangle1LeftEdge = rectangle1.xCenter - getHalf(rectangle1.width);
    float rectangle1RightEdge = rectangle1.xCenter + getHalf(rectangle1.width);

    float rectangle2LeftEdge = rectangle2.xCenter - getHalf(rectangle2.width);
    float rectangle2RightEdge = rectangle2.xCenter + getHalf(rectangle2.width);

    float rectangle1BottomEdge = rectangle1.yCenter - getHalf(rectangle1.height);
    float rectangle1TopEdge = rectangle1.yCenter + getHalf(rectangle1.height);

    float rectangle2BottomEdge = rectangle2.yCenter - getHalf(rectangle2.height);
    float rectangle2TopEdge = rectangle2.yCenter + getHalf(rectangle2.height);

    return rectangle1RightEdge >= rectangle2LeftEdge &&
        rectangle1LeftEdge <= rectangle2RightEdge &&
        rectangle1BottomEdge <= rectangle2TopEdge &&
        rectangle1TopEdge >= rectangle2BottomEdge;
};

bool checkPointToRectangleCollision(Rectangle rectangle, Vector2 point) {
    float rectangleLeftEdge = rectangle.xCenter - getHalf(rectangle.width);
    float rectangleRightEdge = rectangle.xCenter + getHalf(rectangle.width);
    float rectangleTopEdge = rectangle.yCenter + getHalf(rectangle.height);
    float rectangleBottomEdge = rectangle.yCenter - getHalf(rectangle.height);

    return point.x >= rectangleLeftEdge &&
        point.x <= rectangleRightEdge &&
        point.y >= rectangleBottomEdge &&
        point.y <= rectangleTopEdge;
}