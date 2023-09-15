#include "sl.h"
#include "utils/Colors.h"
#include "utils/Rectangles.h"
#include "utils/fonts.h"

void startGame() {
	const int width = 400;
	const int height = 400;

	const Rectangle rectangle = { width * 0.5, height * 0.5, 100, 100 };

	slWindow(width, height, "Simple SIGIL Example", false);

	initFont("src/white_rabbit.ttf");
	setFontSize(80);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		setBackColor(LIGHT_BLUE);
		setForeColor(RED);

		fillRectangle(rectangle);

		writeText("HELLO", { width * 0.5, height * 0.5 }, { 0, 0, 0, 1 });

		slRender();
	}

	slClose();
}
