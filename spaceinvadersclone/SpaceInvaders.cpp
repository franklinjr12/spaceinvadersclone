#include "SpaceInvaders.hpp"
#include "Collisions.hpp"
#include "SpaceInvadersGroups.hpp"

#include <algorithm>

void SpaceInvaders::game_loop() {
	clear_bodies();
}

void SpaceInvaders::game_draw() {
	const int buf_size = 128;
	char text_buffer[buf_size];
	Font font;
	int ypos = 40;
	sprintf_s(text_buffer, "SCORE: %d\n", score);
	font.print(10, ypos, (char*)text_buffer, 1, 1, 1);
	ypos += 20;
}

void SpaceInvaders::clear_bodies() {
	auto current = current_scene->bodies.begin();
	while (current != current_scene->bodies.end()) {
		if ((*current)->collided || (*current)->should_delete) {
			const Body* temp = *current;
			++current;
			if (temp->id != player->id) {
				for(auto it = temp->groups.begin(); it != temp->groups.end(); it++)
					if ((ObjectGroup)(*it) == (ObjectGroup)SpaceInvadersGroups::Enemy)
						score++;
				current_scene->remove_body(temp->id);
				delete temp;
			}
			else
				; //game over
		}
		else {
			++current;
		}
	}
}
