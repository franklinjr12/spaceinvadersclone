#pragma once

#include <Application.hpp>

class SpaceInvaders : public Application {
public:
	SpaceInvaders() {}
	void game_loop() override;
	void game_draw() override;
	void clear_bodies();

	int score = 0;
};

static SpaceInvaders* app;