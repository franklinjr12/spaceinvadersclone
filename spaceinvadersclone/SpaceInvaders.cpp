#include "SpaceInvaders.hpp"
#include "Collisions.hpp"

void SpaceInvaders::game_loop() {
	//clear_enemies();
	//clear_shots();
}

void SpaceInvaders::game_draw() {
	const int buf_size = 128;
	char text_buffer[buf_size];
	Font font;
	int ypos = 40;
	sprintf_s(text_buffer, "SCORE: %d\n", score);
	font.print(10, ypos, (char*)text_buffer, 1, 1, 1);
	ypos += 20;
	Enemy* e = enemies.front();
	sprintf_s(text_buffer, "cx %03f cy %03f\n", e->getX(), e->getY());
	font.print(10, ypos, (char*)text_buffer, 0, 0, 0);
	ypos += 20;
	sprintf_s(text_buffer, "tx %03f ty %03f\n", e->points[0].x, e->points[0].y);
	font.print(10, ypos, (char*)text_buffer, 0, 0, 0);
	ypos += 20;
}

void SpaceInvaders::clear_enemies() {
	auto prev = enemies.before_begin();
	auto current = enemies.begin();
	while (current != enemies.end()) {
		if ((*current)->collided || (*current)->should_delete) {
			Enemy* temp = *current;
			current = enemies.erase_after(prev);
			current_scene->remove_body(temp->id);
			delete temp;
			score++;
		}
		else {
			++prev;
			++current;
		}
	}
}

void SpaceInvaders::clear_shots() {
	auto prev = shots.before_begin();
	auto current = shots.begin();
	while (current != shots.end()) {
		if ((*current)->collided || (*current)->should_delete) {
			Shot* temp = *current;
			current = shots.erase_after(prev);
			delete temp;
		}
		else {
			++prev;
			++current;
		}
	}
}