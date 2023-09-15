#include "sl.h"
#include "utils/Colors.h"
#include "utils/Rectangles.h"

void startGame() {
	const int width = 400;
	const int height = 400;

	const Rectangle rectangle = { width * 0.5, height * 0.5, 100, 100 };

	slWindow(width, height, "Simple SIGIL Example", false);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		setBackColor(LIGHT_BLUE);
		setForeColor(RED);

		fillRectangle(rectangle);

		slRender();
	}

	slClose();
}
