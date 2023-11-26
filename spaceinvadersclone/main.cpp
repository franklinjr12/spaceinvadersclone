#include <iostream>
#include <cstring>
#include <cstdio>
#include <random>
#include "SpaceInvaders.hpp"
#include "PlayerShip.hpp"
#include "Collisions.hpp"

using namespace std;

int main(void) {
	printf("Game init\n");
	app.init();
	Image img("assets/player_ship.png");
	BodyRectangle rect(SCREEN_WIDTH / 2, SCREEN_HEIGHT*0.8, img.width, img.height);
	Body body(img, rect);
	PlayerShip player(body);
	player.handler.callback = [&player](std::vector<event_bytes_type> data) {
		switch (data[0]) {
		case (event_bytes_type)EventType::KeyboardInput:
			if (data[1] == GLFW_PRESS || data[1] == GLFW_REPEAT) {
				switch (data[2]) {
				case GLFW_KEY_RIGHT:
					player.body.vel_x = 5;
					break;
				case GLFW_KEY_LEFT:
					player.body.vel_x = -5;
					break;
				default:
					break;
				}
			}
			if (data[1] == GLFW_RELEASE) {
				switch (data[2]) {
				case GLFW_KEY_RIGHT:
				case GLFW_KEY_LEFT:
					player.body.vel_x = 0;
					break;
				default:
					break;
				}
			}
		case (event_bytes_type)EventType::MouseInput:
			if (data[1] == GLFW_PRESS) {
				switch (data[2]) {
				case GLFW_MOUSE_BUTTON_LEFT: {
					int mx = data[3];
					int my = data[4];
					player.shoot(mx, my);
				}
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


	const int NUM_ENEMIES = 4;
	const int xoffset = 20;
	const int yoffset = 200;
	for (int i = 0; i < NUM_ENEMIES; i++) {
		Enemy* alien = new Enemy(xoffset + i * SCREEN_WIDTH / (NUM_ENEMIES), yoffset);
		app.enemies.push_front(alien);
	}

	Image background_img("assets/spaceinvaders_background.png", SCREEN_WIDTH, SCREEN_HEIGHT);

	Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Scene scene(camera, player.body, background_img, SCREEN_WIDTH, SCREEN_HEIGHT);

	app.current_scene = &scene;

	EventsManager ev_manager;
	ev_manager.subscribe(EventType::KeyboardInput, player.handler);
	ev_manager.subscribe(EventType::MouseInput, player.handler);
	app.events_manager = &ev_manager;

	app.run();

	return 0;
}