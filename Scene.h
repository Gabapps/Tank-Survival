/*
 * Scene.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "Camera.h"
#include "SceneObject.h"
#include "List.h"

typelist(so, SceneObject*)

typedef struct Scene {
	char* name;					//Nom de la scene
	list_so* sceneObjects;	//Tableau contenant les différents objets de la scene
	Script* script;				//Pour associer des fonctions à la scene
	Camera camera;				//Camera liée à la scene
} Scene;

Scene* scene_create(char* name);
void scene_destroy(Scene* scene);
void scene_setup(Scene* scene);
void scene_run(Scene* scene);
void scene_add_so(Scene* scene, SceneObject* so);
int scene_delete_so(Scene* scene, SceneObject* so);
int scene_find_so(Scene* scene, SceneObject* so);

#endif /* SCENE_H_ */
