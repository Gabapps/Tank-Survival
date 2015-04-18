/*
 * Game.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef GAME_H_
#define GAME_H_

#include "Scene.h"


typedef struct Game_s{
	char* name;
	Scene* scene;
	int running;
}Game_s;

Game_s Game;

void game_launch();
//int game_load_scenes();
int game_load_scene(char*);

void game_pause();

void game_resume();

#endif /* GAME_H_ */
