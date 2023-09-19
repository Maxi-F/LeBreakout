#include "Rectangles.h"
#include "Vector.h"
#include "math.h"

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