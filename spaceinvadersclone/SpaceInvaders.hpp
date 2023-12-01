#pragma once

#include <Application.hpp>

class SpaceInvaders : public Application {
public:
	SpaceInvaders() {}
	~SpaceInvaders() {
		if (player)
			delete player;
	}
	void game_loop() override;
	void game_draw() override;
	void clear_bodies();

	int score = 0;
	Scene* game_over;
};

static SpaceInvaders* app;