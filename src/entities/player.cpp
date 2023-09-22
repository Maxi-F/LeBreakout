#include "player.h"

namespace Player {
	static const int PLAYER_LIVES = 3;

	Player initPlayer() {
		return { PLAYER_LIVES };
	}

	bool isStillAlive(Player player) {
		return player.lives > 0;
	};

	void reduceLives(Player& player) {
		player.lives--;
	};
}
