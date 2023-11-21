#pragma once
#include <Application.hpp>

class Shot {
public:
	Shot(int xpos, int ypos, float xdir, float ydir) {
		img = new Image("assets/shoot.png");
		br = new BodyRectangle(xpos, ypos, img->width, img->height);
		body = new Body(*img, *br);
		const float vel = 10;
		body->vel_x = vel * xdir;
		body->vel_y = vel * ydir;
	}
	Image* img;
	BodyRectangle* br;
	Body* body;
};