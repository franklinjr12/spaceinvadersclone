#include "SpaceInvaders.hpp"
#include "Collisions.hpp"

void SpaceInvaders::game_loop() {
	std::vector<Enemy*> remove_e;
	for (auto it = enemies.begin(); it != enemies.end(); ++it) {
		std::vector<Shot*> remove_s;
		for (auto it_s = shots.begin(); it_s != shots.end(); ++it_s) {
			if (isRectColliding((*it)->body->rectangle, (*it_s)->body->rectangle)) {
				remove_s.push_back(*it_s);
				remove_e.push_back(*it);
			}
		}
		for (auto it_s = remove_s.begin(); it_s != remove_s.end(); ++it_s)
			shots.erase(std::remove(shots.begin(), shots.end(), *it_s), shots.end());
	}
	for (auto it = remove_e.begin(); it != remove_e.end(); ++it)
		enemies.erase(std::remove(enemies.begin(), enemies.end(), *it), enemies.end());

}
