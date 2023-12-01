#pragma once

#include "SpaceInvaders.hpp"
#include "SpaceInvadersGroups.hpp"

#include <Application.hpp>
#include <ArcaneTypes.hpp>
#include <ArcaneUtils.hpp>
#include <chrono>

using namespace std::chrono;

enum class EnemyPosition {
	MOVINGUPRIGHT,
	MOVINGDOWNRIGHT,
	MOVINGORIGIN
};

class Enemy : public DynamicBody {
public:
	Enemy(Vecf pos, float velocity = -1) {
		image = new Image("assets/alien.png");
		//image = new Image("assets/alien_sprite.png");
		rectangle = new BodyRectangle(pos, image->width, image->height);
		suffer_gravity = false;
		position_enum = EnemyPosition::MOVINGUPRIGHT;
		setX(pos[0]);
		setY(pos[1]);
		points[0].x = pos[0];
		points[0].y = pos[1];
		points[1].x = points[0].x + distance;
		points[1].y = points[0].y - distance;
		points[2].x = points[1].x + distance;
		points[2].y = points[1].y + distance;
		float dirx = points[1].x - getX();
		float diry = points[1].y - getY();
		float mag = sqrt(dirx * dirx + diry * diry);
		if (velocity == -1) velocity = rand() % 5 + 1;
		vel_mult = velocity;
		vel[0] = dirx * vel_mult / mag;
		vel[1] = diry * vel_mult / mag;
		groups.push_back((ObjectGroup)SpaceInvadersGroups::Enemy);
		tp = system_clock::now();
	}

	~Enemy() {
	}

	void _update() override {
		process_shoot();
		Point current;
		current.x = getX();
		current.y = getY();
		switch (position_enum) {
		case EnemyPosition::MOVINGORIGIN:
			if (DistanceVecf(current.pos, points[0].pos) < threashold) {
				position_enum = EnemyPosition::MOVINGUPRIGHT;
				float dirx = points[1].x - getX();
				float diry = points[1].y - getY();
				float mag = MagVecf(Vecf{ dirx,diry });
				vel[0] = dirx * vel_mult / mag;
				vel[1] = diry * vel_mult / mag;
			}
			break;
		case EnemyPosition::MOVINGUPRIGHT:
			if (DistanceVecf(current.pos, points[1].pos) < threashold) {
				position_enum = EnemyPosition::MOVINGDOWNRIGHT;
				float dirx = points[2].x - getX();
				float diry = points[2].y - getY();
				float mag = MagVecf(Vecf{ dirx,diry });
				vel[0] = dirx * vel_mult / mag;
				vel[1] = diry * vel_mult / mag;
			}
			break;
		case EnemyPosition::MOVINGDOWNRIGHT:
			if (DistanceVecf(current.pos, points[2].pos) < threashold) {
				position_enum = EnemyPosition::MOVINGORIGIN;
				float dirx = points[0].x - getX();
				float diry = points[0].y - getY();
				float mag = MagVecf(Vecf{ dirx,diry });
				vel[0] = dirx * vel_mult / mag;
				vel[1] = diry * vel_mult / mag;
			}
			break;
		}
	}
	void process_shoot() {
		auto t = system_clock::now() - tp;
		if (duration_cast<milliseconds>(t).count() > shoot_timeout_ms) {
			tp = system_clock::now();
			shoot(getX(), getY() + 10);
		}
	}
	void shoot(int x, int y) {
		float dirx, diry, mag;
		dirx = x - getX();
		diry = y - getY();
		Vecf dir = { dirx, diry };
		mag = MagVecf(dir);
		dir[0] = dir[0] / mag;
		dir[1] = dir[1] / mag;
		Vecf p1 = { getX(), getY() + image->height / 2 + 10 };
		Shot* shot = new Shot(p1, dir);
		shot->owner_id = id;
		app->current_scene->add_body(shot);
	}

	void handle_collision(ObjectId _id) override {
		// get the shot it colldided
		Shot* shot = (Shot*)app->current_scene->bodies_map[_id];
		if (shot->owner_id == id)
			collided = false;
	};

	Point points[3];
	EnemyPosition position_enum;
	const int distance = 100;
	const int threashold = 10;
	float vel_mult = 5;
	const int shoot_timeout_ms = 1000;
	system_clock::time_point tp;
};