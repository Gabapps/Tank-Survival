/*
 * Game.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "List.h"
#include "Time.h"
#include "Window.h"
#include "Audio.h"

typelist(scene, Scene*);

typedef struct Game_s{
	char* name;
	Scene* scene;
	Scene* scene_to_load;
	list_scene* scenes;
	int running;
}Game_s;

Game_s Game;

//Launch the game
void game_init();

//Load a scene by name
void game_load_scene(char* name);

//Reload the current scene
void game_reload_current_scene();

//Add a scene to the game
void game_add_scene(Scene *scene);

//Pause the game
void game_pause();

//Resume the game
void game_resume();

//Update the game
void game_update();

//Exit the game
void game_exit();

#endif /* GAME_H_ */
