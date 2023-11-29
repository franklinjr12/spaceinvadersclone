#pragma once
#include "SpaceInvaders.hpp"
#include "Shot.hpp"

class PlayerShip : public Player {
public:
	PlayerShip(Image* img, BodyRectangle* rect) : Player(img, rect) {
	}
	void shoot(int x, int y) {
		float dirx, diry, mag;
		dirx = x - getX();
		diry = y - getY();
		mag = sqrt(dirx * dirx + diry * diry);
		dirx = dirx / mag;
		diry = diry / mag;
		Shot* shot = new Shot(getX(), getY() - 10, dirx, diry);
		app.shots.push_front(shot);
		//app.current_scene->bodies.push_back(shot->body);
	}
};