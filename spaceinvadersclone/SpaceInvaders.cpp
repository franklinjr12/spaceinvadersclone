#include "SpaceInvaders.hpp"
#include "Collisions.hpp"

void SpaceInvaders::game_loop() {
	player->body.update();
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
	//const int buf_size = 128;
	//char text_buffer[buf_size];
	//Font font;
	//sprintf_s(text_buffer, "cp: %03d %03d\n", (int)player->body.getX(), player->body.getY());
	//font.print(10, 40, (char*)text_buffer);
	//sprintf_s(text_buffer, "cv: %03d %03d\n", (int)player->body.vel_x, player->body.vel_y);
	//font.print(10, 60, (char*)text_buffer);

	if (!enemies.empty()) {
		auto e = enemies.front();
		const int buf_size = 128;
		char text_buffer[buf_size];
		Font font;
		sprintf_s(text_buffer, "cp: %03d %03d\n", e->body->getX(), e->body->getY());
		font.print(10, 40, (char*)text_buffer, 1, 1, 1);
		sprintf_s(text_buffer, "tp: %03d %03d\n", e->positions[1].x, e->positions[1].y);
		font.print(10, 60, (char*)text_buffer, 1, 1, 1);
		sprintf_s(text_buffer, "cv: %03f %03f\n", e->body->vel_x, e->body->vel_y);
		font.print(10, 80, (char*)text_buffer, 1, 1, 1);
	}


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