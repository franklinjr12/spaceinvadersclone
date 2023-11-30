#pragma once

#include "SpaceInvaders.hpp"
#include "Shot.hpp"

#include <ArcaneUtils.hpp>

class PlayerShip : public Player {
public:
	PlayerShip(Image* img, BodyRectangle* rect) : Player(img, rect) {
	}
	void shoot(int x, int y) {
		float dirx, diry, mag;
		dirx = x - getX();
		diry = y - getY();
		Vecf dir = { dirx, diry };
		mag = MagVecf(dir);
		dir[0] = dir[0] / mag;
		dir[1] = dir[1] / mag;
		Vecf p1 = { getX(), getY() - image->height/2 - 10};
		Shot* shot = new Shot(p1, dir);
		app->current_scene->add_body(shot);
	}

};