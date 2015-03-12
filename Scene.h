/*
 * Scene.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "GameEngine.h"
#include "Camera.h"

struct Scene {
	char* name;
	SceneObject* sceneObjects;
	int count;
	Script* script;
	Camera camera;
};

Scene* scene_create();
void scene_destroy(Scene* scene);
void scene_setup(Scene* scene);
void scene_run(Scene* scene);
void scene_add_so(SceneObject* so);
int scene_delete_so(SceneObject* so);
SceneObject* scene_find_so(SceneObject* so);

#endif /* SCENE_H_ */
