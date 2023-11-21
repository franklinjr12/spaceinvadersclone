#include <iostream>
#include <cstring>
#include <cstdio>
#include <Application.hpp>
#include <windows.h>
using namespace std;

class SpaceInvaders : public Application {
public:
	SpaceInvaders() {}
	void game_loop() override {

	}
	void game_draw() override {

	}

};

int main(void) {
	SpaceInvaders app;
	app.init();

	Image img("assets/player_ship.png");
	BodyRectangle rect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, img.width, img.height);
	Body body(img, rect);
	Player player(body);
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
	//ev_manager.subscribe(EventType::KeyboardInput, player.handler);
	app.events_manager = &ev_manager;

	app.run();

	return 0;
}