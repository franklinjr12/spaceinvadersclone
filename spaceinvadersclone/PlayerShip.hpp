#pragma once
#include "SpaceInvaders.hpp"
#include "Shot.hpp"

class PlayerShip : public Player {
public:
	PlayerShip(Body& body) : Player(body) {
	}
	void shoot(int x, int y) {
		float dirx, diry, mag;
		dirx = x - body.getX();
		diry = y - body.getY();
		mag = sqrt(dirx * dirx + diry * diry);
		dirx = dirx / mag;
		diry = diry / mag;
		Shot* shot = new Shot(body.getX(), body.getY() - 20, dirx, diry);
		//app.shots.push_back(shot);
		app.shots.push_front(shot);
		app.current_scene->bodies.push_back(shot->body);
		//new Shot(body.getX(), body.getY() - 20, dirx, diry);
	}
};