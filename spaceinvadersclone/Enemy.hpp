#pragma once

#include <Application.hpp>

enum class EnemyPosition {
	MOVINGUPRIGHT,
	MOVINGDOWNRIGHT,
	MOVINGORIGIN
};


struct Position {
	int x;
	int y;
};

int distancePosition(Position p1, Position p2) {
	auto a = p1.x - p2.x;
	auto b = p1.y - p2.y;
	return sqrt(a * a + b * b);
}


class Enemy {
public:
	Enemy(int xpos, int ypos) {
		img = new Image("assets/alien_sprite.png");
		br = new BodyRectangle(xpos, ypos, img->width, img->height);
		body = new Body(*img, *br);
		body->suffer_gravity = false;
		position_enum = EnemyPosition::MOVINGUPRIGHT;
		positions[0].x = xpos;
		positions[0].y = ypos;
		positions[1].x = positions[0].x + distance;
		positions[1].y = positions[0].y - distance;
		positions[2].x = positions[1].x + distance;
		positions[2].y = positions[1].y + distance;
		float dirx = positions[1].x - positions[0].x;
		float diry = positions[1].y - positions[0].y;
		float mag = sqrt(dirx * dirx + diry * diry);
		body->vel_x = dirx * vel / mag;
		body->vel_y = diry * vel / mag;
	}
	~Enemy() {
		if (img) delete img;
		if (br) delete br;
		if (body) delete body;
	}
	void update() {
		body->update();
		Position current;
		current.x = body->getX();
		current.y = body->getY();
		switch (position_enum) {
		case EnemyPosition::MOVINGORIGIN:
			if (distancePosition(current, positions[0]) < threashold) {
				position_enum = EnemyPosition::MOVINGUPRIGHT;
				float dirx = positions[1].x - body->getX();
				float diry = positions[1].y - body->getY();
				float mag = sqrt(dirx * dirx + diry * diry);
				body->vel_x = dirx * vel / mag;
				body->vel_y = diry * vel / mag;
			}
			break;
		case EnemyPosition::MOVINGUPRIGHT:
			if (distancePosition(current, positions[1]) < threashold) {
				position_enum = EnemyPosition::MOVINGDOWNRIGHT;
				float dirx = positions[2].x - body->getX();
				float diry = positions[2].y - body->getY();
				float mag = sqrt(dirx * dirx + diry * diry);
				body->vel_x = dirx * vel / mag;
				body->vel_y = diry * vel / mag;
			}
			break;
		case EnemyPosition::MOVINGDOWNRIGHT:
			if (distancePosition(current, positions[2]) < threashold) {
				position_enum = EnemyPosition::MOVINGORIGIN;
				float dirx = positions[0].x - body->getX();
				float diry = positions[0].y - body->getY();
				float mag = sqrt(dirx * dirx + diry * diry);
				body->vel_x = dirx * vel / mag;
				body->vel_y = diry * vel / mag;
			}
			break;
		}
	}
	Position positions[3];
	EnemyPosition position_enum;
	bool should_delete = false;
	Image* img;
	BodyRectangle* br;
	Body* body;
	const int distance = 100;
	const int threashold = 10;
	const float vel = 5;
};