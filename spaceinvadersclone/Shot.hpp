#pragma once
#include <Application.hpp>

class Shot : public DynamicBody {
public:

	Shot(Vecf pos, Vecf dir) {
		image = new Image("assets/shoot.png");
		rectangle = new BodyRectangle(pos, image->width, image->height);
		setX(pos[0]);
		setY(pos[1]);
		suffer_gravity = false;
		const float vel_mult = 10;
		vel[0] = vel_mult * dir[0];
		vel[1] = vel_mult * dir[1];
	}
	~Shot() {
		if (image) delete image;
		if (rectangle) delete rectangle;
	}

	void handle_collision(ObjectId id) override {
		should_delete = true;
	};
};