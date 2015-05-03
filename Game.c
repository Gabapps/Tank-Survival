/*
 * Game.c

 *
 *  Created on: 17 avr. 2015
 *      Author: Gabriel
 */
#include "Game.h"

void game_load_scene_direct(Scene* scene);

void game_init() {
	Game.running = 0;
	Game.scene = NULL;
	Game.scene_to_load = NULL;
	Game.scenes = list_scene_create();
}

void game_pause() {
	Game.running = 0;
}

void game_resume() {
	Game.running = 1;
}

void game_update() {
	if(Game.scene_to_load) {
		game_load_scene_direct(Game.scene_to_load);
		Game.scene_to_load = NULL;
	}
}

void game_load_scene_direct(Scene* scene) {
	if(Game.scene) scene_destroy_content(Game.scene);
	Game.scene = scene;
    time_init();
	scene_setup(scene);
}

void game_load_scene(char* name) {
	node_scene* iterator = Game.scenes->root;

	while(iterator != NULL) {
		if(strcmp(name, iterator->value->name) == 0) {
			Game.scene_to_load = iterator->value;
		}
		iterator = iterator->next;
	}
}

void game_reload_current_scene() {
	Game.scene_to_load = Game.scene;
}

void game_add_scene(Scene *scene) {
	list_scene_put(Game.scenes, scene);
}

void game_exit() {
	window_close();
}
