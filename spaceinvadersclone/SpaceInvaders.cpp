#include "SpaceInvaders.hpp"
#include "Collisions.hpp"

void SpaceInvaders::game_loop() {
	auto prev = enemies.before_begin();
	auto current = enemies.begin();
	while (current != enemies.end()) {
		(*current)->body->update();
		auto prev_s = shots.before_begin();
		auto current_s = shots.begin();
		while (current_s != shots.end()) {
			if (isRectColliding((*current)->body->rectangle, (*current_s)->body->rectangle)) {
				printf("got a collision!!\n");
				(*current)->should_delete = true;
				(*current_s)->should_delete = true;
			}
			if ((*current_s)->should_delete)
				current_s = shots.erase_after(prev_s);
			else {
				++prev_s;
				++current_s;
			}
		}
		if ((*current)->should_delete)
			current = enemies.erase_after(prev);
		else {
			++prev;
			++current;
		}
	}

	auto prev_s = shots.before_begin();
	auto current_s = shots.begin();
	while (current_s != shots.end()) {
		(*current_s)->body->update();
		if ((*current_s)->should_delete)
			current_s = shots.erase_after(prev_s);
		else {
			++prev_s;
			++current_s;
		}

	}
}

void SpaceInvaders::game_draw() {
	auto current = enemies.begin();
	while (current != enemies.end()) {
		(*current)->body->draw();
		++current;
	}
	auto current_s = shots.begin();
	while (current_s != shots.end()) {
		(*current_s)->body->draw();
		++current_s;
	}
}