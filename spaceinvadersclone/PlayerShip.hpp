#pragma once

#include "SpaceInvaders.hpp"
#include "Shot.hpp"

#include <ArcaneUtils.hpp>
#include <chrono>

using namespace std::chrono;

class PlayerShip : public Player {
public:
	PlayerShip(Image* img, BodyRectangle* rect) : Player(img, rect) {
		tp = system_clock::now();
	}

	void shoot(int x, int y) {
		auto t = system_clock::now() - tp;
		if (duration_cast<milliseconds>(t).count() > shoot_timeout_ms) {
			tp = system_clock::now();
			float dirx, diry, mag;
			dirx = x - getX();
			diry = y - getY();
			Vecf dir = { dirx, diry };
			mag = MagVecf(dir);
			dir[0] = dir[0] / mag;
			dir[1] = dir[1] / mag;
			Vecf p1 = { getX(), getY() - image->height / 2 - 10 };
			Shot* shot = new Shot(p1, dir);
			shot->owner_id = id;
			app->current_scene->add_body(shot);
		}
	}
	void handle_collision(ObjectId _id) override {
		// get the shot it colldided
		Shot* shot = (Shot*)app->current_scene->bodies_map[_id];
		if (shot->owner_id == id)
			collided = false;
	};

	const int shoot_timeout_ms = 300;
	system_clock::time_point tp;
};