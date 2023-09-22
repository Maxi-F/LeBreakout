#pragma once

namespace Player {
	struct Player {
		int lives;
	};

	Player initPlayer();
	bool isStillAlive(Player player);
	void reduceLives(Player& player);
}
