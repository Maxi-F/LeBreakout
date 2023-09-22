#pragma once
#include "Rectangles.h"
#include "Vector.h"

double getHalf(double value);
double clamp(double value, double min, double max);
double getDistanceFromMiddle(Rectangle rectangle, Vector2 point);
double moduleOf(double value);
int getRandomBetween(int min, int max);