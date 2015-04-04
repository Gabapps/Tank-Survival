/*
 * SceneScript.h
 *
 *  Created on: 19 mars 2015
 *      Author: Gabriel
 */

#ifndef SCRIPTS_SCENESCRIPT_H_
#define SCRIPTS_SCENESCRIPT_H_

#include "Tank.h"
#include <stdio.h>
#include "../Ressources.h"

#define MAPHEIGHT 30
#define MAPWIDTH 30

#define MAX_PLAYER 4

typedef struct SceneScript {
	define_script(SceneScript);
	float spawnpoints[MAX_PLAYER*2]; // 4 spawns with 2 coords each
} SceneScript;

void sc_map(SceneScript* scscript);
void sc_controls();
void sc_loadplayers(SceneScript* scscript);

void sc_setup(SceneScript* scenescript, SceneObject* so) {
	ressources_init();
	ressources_load();

	Camera cam;
	camera_init(&cam);
	vec3 pos = {30,30,15},
			center = {15,0,15},
			up = {0,1,0};
	camera_look_at(&cam, pos, center, up);
	camera_refresh_matrices(&cam);
	// Day color : {1,0.94,0.5}; force : 1
	// Moonlight color :{0,0,0.8}; force : 0.3
	vec3 poslight = {5,30,5},
			dirlight = {-1,-1,-0.1},
			colorlight = {1,0.94,0.5};

	Game.scene->camera = cam;
	Game.scene->light = sunlight_create(poslight, dirlight, colorlight, 1);

	sc_controls();
	sc_map(scenescript);
	sc_loadplayers(scenescript);
}

void sc_run(SceneScript* scenescript, SceneObject* so) {
	vec3 dir = {cos(0.1*Time.timeSinceStart),-1,sin(0.1*Time.timeSinceStart)};
	sunlight_set_direction(&(Game.scene->light), dir);
}

void sc_map(SceneScript* scscript)
{
	int i, j, test;
	Transform transform_map = transform_origin();

	SceneObject *map_wall = so_create("Wall", transform_origin());

	map_wall->shader = ressources_get_shader(SHADER_TEXTURE);
	map_wall->mesh = ressources_get_mesh(MESH_WALL);
	map_wall->texture = ressources_get_texture(TEXTURE_WALL);

	FILE* map = fopen("Map/map.txt", "r");
	if (map == NULL)
		fprintf(stderr, "Failed to open map.txt");
	int nbspawn = 0;
	for(i=0;i<MAPHEIGHT;++i)
	{
		for(j=0;j<MAPWIDTH;++j)
		{
			transform_map = transform_origin();
			vec3 vec = {i,0,MAPWIDTH-j-1};
			transform_translate_world(&transform_map, vec);
			fscanf(map, "%d ", &test);
			if(test == 1)
			{
				scene_add_so(Game.scene, so_duplicate(map_wall, "wall", transform_map));
			}
			else if(test == 2) {
				scscript->spawnpoints[nbspawn*2]=(float)j;
				scscript->spawnpoints[nbspawn*2+1]=(float)i;
				nbspawn++;
			}
		}
		fscanf(map, "\n");
	}
	fclose(map);

}

void sc_controls() {
	init_controlsTable();

	controls_create("P1_up", GLFW_KEY_UP);
	controls_create("P1_down", GLFW_KEY_DOWN);
	controls_create("P1_left", GLFW_KEY_LEFT);
	controls_create("P1_right", GLFW_KEY_RIGHT);

	controls_create("P2_up", GLFW_KEY_Z);
	controls_create("P2_down", GLFW_KEY_S);
	controls_create("P2_left", GLFW_KEY_Q);
	controls_create("P2_right", GLFW_KEY_D);

	controls_create("P3_up", GLFW_KEY_Y);
	controls_create("P3_down", GLFW_KEY_H);
	controls_create("P3_left", GLFW_KEY_G);
	controls_create("P3_right", GLFW_KEY_J);

	controls_create("P4_up", GLFW_KEY_KP_5);
	controls_create("P4_down", GLFW_KEY_KP_6);
	controls_create("P4_left", GLFW_KEY_KP_3);
	controls_create("P4_right", GLFW_KEY_KP_9);
}

void sc_loadplayers(SceneScript* scscript) {
	int i;
	for(i=0; i<MAX_PLAYER; i++) {
		Tank *script = malloc(sizeof(Tank));
		script->name = "Tank";
		script->setup = tank_setup;
		script->run = tank_run;
		script->player = i;

		SceneObject *tank = so_create("Tank", transform_xyz(scscript->spawnpoints[i*2],0,scscript->spawnpoints[i*2+1]));
		so_add_script(tank, (Script*)script);
		scene_add_so(Game.scene, tank);
	}
}
#endif /* SCRIPTS_SCENESCRIPT_H_ */
