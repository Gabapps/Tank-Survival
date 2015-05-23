/*
 * Game.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef GAME_H_
#define GAME_H_

#include "Scene.h"
#include "List.h"
#include "Time.h"
#include "Window.h"

typelist(scene, Scene*);

typedef struct Game_s{
	char* name;
	Scene* scene;
	Scene* scene_to_load;
	list_scene* scenes;
	int running;
}Game_s;

Game_s Game;

void game_init();

void game_launch();
//int game_load_scenes();
void game_load_scene(char* name);

void game_reload_current_scene();

void game_add_scene(Scene *scene);

void game_pause();

void game_resume();

void game_update();

void game_exit();

#endif /* GAME_H_ */
