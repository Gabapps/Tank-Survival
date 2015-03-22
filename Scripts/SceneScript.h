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

#define MAPHEIGHT 30
#define MAPWIDTH 30

typedef struct SceneScript {
	define_script(SceneScript);
} SceneScript;

void sc_map(Shader* shader);

void sc_setup(SceneScript* scenescript, SceneObject* so) {
	Shader *shader = shader_create("Shaders/vertex.vert", "Shaders/fragment.frag");
	shader_load(shader);

	Mesh *mesh = mesh_create();
	mesh_load_from_obj(mesh, "Models/Tank.obj");

	Tank *script = malloc(sizeof(Tank));
	script->name = "Tank";
	script->setup = tank_setup;
	script->run = tank_run;

	SceneObject *tank = so_create("Tank", transform_xyz(3,0,3));
	so_add_script(tank, (Script*)script);
	tank->mesh = mesh;
	tank->shader = shader;

	Camera cam;
	camera_init(&cam);
	vec3 pos = {30,45,30},
			center = {15,0,15},
			up = {0,1,0};
	//vec3_add(cam.transform.position, cam.transform.position, pos);
	transform_look_at(&(cam.transform),pos, center,up);

	Game.scene->camera = cam;

	init_controlsTable();

	controls_create("P1_up", GLFW_KEY_UP);
	controls_create("P1_down", GLFW_KEY_DOWN);
	controls_create("P1_left", GLFW_KEY_LEFT);
	controls_create("P1_right", GLFW_KEY_RIGHT);

	scene_add_so(Game.scene, tank);
	sc_map(shader);
}

void sc_run(SceneScript* tank, SceneObject* so) {

}

void sc_map(Shader* shader)
{
	int i, j, test;

	Transform transform_map = transform_origin();
	Mesh *mesh_map_wall = mesh_create();
	mesh_load_from_obj(mesh_map_wall, "Models/Wall.obj");
	SceneObject *map_wall = so_create("map_wall", transform_origin());
	map_wall->mesh = mesh_map_wall;
	map_wall->name = "wall";
	map_wall->shader = shader;

	FILE* map = fopen("Map/map.txt", "r");
	if (map == NULL)
		fprintf(stderr, "Failed to open map.txt");

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
		}
		fscanf(map, "\n");
	}
	fclose(map);

}

#endif /* SCRIPTS_SCENESCRIPT_H_ */
