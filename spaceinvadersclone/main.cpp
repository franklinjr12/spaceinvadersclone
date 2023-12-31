#include "SpaceInvaders.hpp"
#include "PlayerShip.hpp"
#include "Enemy.hpp"

#include <Collisions.hpp>
#include <ArcaneVersion.hpp>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <random>

using namespace std;

int main(void) {
	printf("Game init\n");
	printf("Arcane Engine version %s\n", arcane_version_string().c_str());
	app = new SpaceInvaders();
	app->init();
	Image* img = new Image("assets/own_ship.png");
	//Image* img = new Image("assets/player_ship.png");
	Vecf p1 = {SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.8};
	BodyRectangle* rect = new BodyRectangle(p1, img->width, img->height);
	PlayerShip* player = new PlayerShip(img, rect);
	player->handler.callback = [player](std::vector<event_bytes_type> data) {
		if (app->current_scene->name == "game over") return; // very bad way to do but works
		switch (data[0]) {
		case (event_bytes_type)EventType::KeyboardInput:
			if (data[1] == GLFW_PRESS || data[1] == GLFW_REPEAT) {
				switch (data[2]) {
				case GLFW_KEY_RIGHT:
					player->vel[0] = 5;
					break;
				case GLFW_KEY_LEFT:
					player->vel[0] = -5;
					break;
				default:
					break;
				}
			}
			if (data[1] == GLFW_RELEASE) {
				switch (data[2]) {
				case GLFW_KEY_RIGHT:
				case GLFW_KEY_LEFT:
					player->vel[0] = 0;
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
					player->shoot(mx, my);
				}
				default:
					break;
				}
			}
		default:
			break;
		}
		};

	player->suffer_gravity = false;

	app->player = player;

	Image background_img("assets/spaceinvaders_background.png", SCREEN_WIDTH, SCREEN_HEIGHT);

	Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Scene game_over(&camera, &background_img, SCREEN_WIDTH, SCREEN_HEIGHT);
	game_over.name = "game over";
	app->game_over = &game_over;

	Scene scene(&camera, &background_img, SCREEN_WIDTH, SCREEN_HEIGHT);

	app->current_scene = &scene;

	scene.add_body(player);

	const int NUM_ENEMIES = 4;
	const int xoffset = 20;
	const int yoffset = 200;
	for (int i = 0; i < NUM_ENEMIES; i++) {
		Vecf p2 = { xoffset + i * SCREEN_WIDTH / (NUM_ENEMIES), yoffset };
		Enemy* alien = new Enemy(p2);
		scene.add_body(alien);
	}


	EventsManager ev_manager;
	ev_manager.subscribe(EventType::KeyboardInput, player->handler);
	ev_manager.subscribe(EventType::MouseInput, player->handler);
	app->events_manager = &ev_manager;

	app->run();

	delete app;

	return 0;
}