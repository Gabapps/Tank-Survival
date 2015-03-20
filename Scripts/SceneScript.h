/*
 * SceneScript.h
 *
 *  Created on: 19 mars 2015
 *      Author: Gabriel
 */

#ifndef SCRIPTS_SCENESCRIPT_H_
#define SCRIPTS_SCENESCRIPT_H_

#include "Tank.h"

typedef struct SceneScript {
	define_script(SceneScript);
} SceneScript;

void sc_duplicate_so(SceneObject *tank);

void sc_setup(SceneScript* scenescript, SceneObject* so) {
	Shader *shader = shader_create("Shaders/vertex.vert", "Shaders/fragment.frag");
	shader_load(shader);

	Mesh *mesh = mesh_create();
	mesh_load_from_obj(mesh, "Models/Tank.obj");

	Tank *script = malloc(sizeof(Tank));
	script->name = "Tank";
	script->setup = tank_setup;
	script->run = tank_run;

	SceneObject *tank = so_create("Tank", transform_origin());
	so_add_script(tank, (Script*)script);
	tank->mesh = mesh;
	tank->shader = shader;

	Camera cam;
	camera_init(&cam);
	vec3 pos = {-10,3,-10},
			center = {0,0,0},
			up = {0,1,0};
	//vec3_add(cam.transform.position, cam.transform.position, pos);
	transform_look_at(&(cam.transform),pos, center,up);

	sc_duplicate_so(tank);

	Game.scene->camera = cam;

	init_controlsTable();

	controls_create("P1_up", GLFW_KEY_UP);
	controls_create("P1_down", GLFW_KEY_DOWN);
	controls_create("P1_left", GLFW_KEY_LEFT);
	controls_create("P1_right", GLFW_KEY_RIGHT);

	scene_add_so(Game.scene, tank);
}

void sc_run(SceneScript* tank, SceneObject* so) {

}

void sc_duplicate_so(SceneObject *tank) {
	int i;

	for(i=0; i<10; i++) {
		vec3 delta = {i*3,0,0};
		SceneObject* new_tank = so_duplicate(tank, "Tank", tank->transform);
		transform_translate(&(new_tank->transform), delta);
		scene_add_so(Game.scene, new_tank);
	}
}

#endif /* SCRIPTS_SCENESCRIPT_H_ */
