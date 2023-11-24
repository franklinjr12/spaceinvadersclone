#pragma once

#include <Application.hpp>
#include <vector>
#include <forward_list>
#include "Shot.hpp"
#include "Enemy.hpp"
#include "Collisions.hpp"

class SpaceInvaders : public Application {
public:
	//std::vector<Shot*> shots;
	std::forward_list<Shot*> shots;
	//std::vector<Enemy*> enemies;
	std::forward_list<Enemy*> enemies;
	SpaceInvaders() {}
	void game_loop() override;
	void game_draw() override;
};

static SpaceInvaders app;