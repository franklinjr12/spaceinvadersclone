#pragma once
#include <Application.hpp>

class Shot {
public:
	Shot(int xpos, int ypos, float xdir, float ydir) {
		img = new Image("assets/shoot.png");
		br = new BodyRectangle(xpos, ypos, img->width, img->height);
		body = new Body(*img, *br);
		body->suffer_gravity = false;
		const float vel = 10;
		body->vel_x = vel * xdir;
		body->vel_y = vel * ydir;
	}
	~Shot() {
		if (img) delete img;
		if (br) delete br;
		if (body) delete body;
	}
	bool should_delete = false;
	Image* img;
	BodyRectangle* br;
	Body* body;
};