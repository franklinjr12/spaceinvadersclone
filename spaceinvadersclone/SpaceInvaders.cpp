#include "SpaceInvaders.hpp"
#include "Collisions.hpp"

void SpaceInvaders::game_loop() {
	auto prev = enemies.before_begin();
	auto current = enemies.begin();
	while (current != enemies.end()) {
		(*current)->update();
		auto prev_s = shots.before_begin();
		auto current_s = shots.begin();
		while (current_s != shots.end()) {
			if (isRectColliding((*current)->body->rectangle, (*current_s)->body->rectangle)) {
				(*current)->should_delete = true;
				(*current_s)->should_delete = true;
			}
			if ((*current_s)->should_delete) {
				Shot* temp = *current_s;
				current_s = shots.erase_after(prev_s);
				delete temp;
			}
			else {
				++prev_s;
				++current_s;
			}
		}
		if ((*current)->should_delete) {
			Enemy* temp = *current;
			current = enemies.erase_after(prev);
			delete temp;
			score++;
		}
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
	const int buf_size = 128;
	char text_buffer[buf_size];
	Font font;
	sprintf_s(text_buffer, "SCORE: %d\n", score);
	font.print(10, 40, (char*)text_buffer, 1, 1, 1);
}