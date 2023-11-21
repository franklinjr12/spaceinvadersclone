#include <iostream>
#include <cstring>
#include <cstdio>
#include "SpaceInvaders.hpp"
#include "PlayerShip.hpp"

using namespace std;


int main(void) {
	printf("Game init2\n");
	app.init();
	Image img("assets/player_ship.png");
	BodyRectangle rect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, img.width, img.height);
	Body body(img, rect);
	PlayerShip player(body);
	int* mx = (int*)&app.mouse_xpos;
	int* my = (int*)&app.mouse_ypos;
	player.handler.callback = [&player, &mx, &my](std::vector<event_bytes_type> data) {
		switch (data[0]) {
		case (event_bytes_type)EventType::KeyboardInput:
			// if (action == GLFW_PRESS) printf("key %d scancode %d name '%s'\n", key, scancode, key_name);
			if (data[1] == GLFW_PRESS) {
				switch (data[2]) {
				case GLFW_KEY_RIGHT:
					player.body.setX(player.body.getX() + 5);
					break;
				case GLFW_KEY_LEFT:
					player.body.setX(player.body.getX() - 5);
					break;
				default:
					break;
				}
			}
		case (event_bytes_type)EventType::MouseInput:
			if (data[1] == GLFW_PRESS) {
				switch (data[2]) {
				case GLFW_MOUSE_BUTTON_LEFT:
					player.shoot(*mx, *my);
				default:
					break;
				}
			}
		default:
			break;
		}
		};



	player.body.suffer_gravity = false;

	app.player = &player;

	Image img_alien("assets/alien_sprite.png");
	BodyRectangle rect_alien(SCREEN_WIDTH / 2, 100, img_alien.width, img_alien.height);
	Body body_alien(img_alien, rect_alien);
	body_alien.suffer_gravity = false;

	Image background_img("assets/space_background.png", SCREEN_WIDTH, SCREEN_HEIGHT);

	Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Scene scene(camera, player.body, background_img, SCREEN_WIDTH, SCREEN_HEIGHT);
	scene.bodies.push_back(&body_alien);

	app.current_scene = &scene;

	EventsManager ev_manager;
	ev_manager.subscribe(EventType::KeyboardInput, player.handler);
	ev_manager.subscribe(EventType::MouseInput, player.handler);
	app.events_manager = &ev_manager;

	app.run();

	return 0;
}