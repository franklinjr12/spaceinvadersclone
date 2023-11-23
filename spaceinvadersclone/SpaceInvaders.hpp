#pragma once

#include <Application.hpp>
#include <vector>
#include "Shot.hpp"
#include "Enemy.hpp"
#include "Collisions.hpp"

class SpaceInvaders : public Application {
public:
	std::vector<Shot*> shots;
	std::vector<Enemy*> enemies;
	SpaceInvaders() {}
	void game_loop() override;
	void game_draw() override {

	}
};

static SpaceInvaders app;