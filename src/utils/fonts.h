#pragma once
#include "Colors.h"
#include "Vector.h"

void writeText(const char* text, Vector2 position, Color color, int fontSize);
void initFont(const char* filename);
void setFontSize(int fontSize);
