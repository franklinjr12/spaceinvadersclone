#pragma once
#include "SpaceInvaders.hpp"
#include "Shot.hpp"

class PlayerShip : public Player {
public:
	PlayerShip(Body& body) : Player(body) {
	}
	void shoot(int x, int y) {
		float dirx, diry, mag;
		const int middle = body.getX() + body.rectangle.w / 2;
		dirx = x - middle;
		diry = y - body.getY();
		mag = sqrt(dirx * dirx + diry * diry);
		dirx = dirx / mag;
		diry = diry / mag;
		Shot* shot = new Shot(middle, body.getY() - 10, dirx, diry);
		app.shots.push_front(shot);
		//app.current_scene->bodies.push_back(shot->body);
	}
};