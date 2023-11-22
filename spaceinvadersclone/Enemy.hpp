#pragma once

#include <Application.hpp>


class Enemy {
public:
	Enemy(int xpos, int ypos) {
		img = new Image("assets/alien_sprite.png");
		br = new BodyRectangle(xpos, ypos, img->width, img->height);
		body = new Body(*img, *br);
		body->suffer_gravity = false;
	}
	~Enemy() {
		if (img) delete img;
		if (br) delete br;
		if (body) delete body;
	}
	Image* img;
	BodyRectangle* br;
	Body* body;

};