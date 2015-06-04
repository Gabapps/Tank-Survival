/**
 * @file Scene.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 1 March 2015
 * @brief A scene contain sceneObjects, a camera, lights etc.
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "Camera.h"
#include "SceneObject.h"
#include "List.h"
#include "SunLight.h"
#include "GUI/GUI.h"
#include "Audio.h"

typelist(so, SceneObject*);

typedef struct Scene {
	char* name;					//Nom de la scene
	list_so* sceneObjects;	//Tableau contenant les différents objets de la scene
	Script* script;				//Pour associer des fonctions à la scene
	Camera camera;				//Camera liée à la scene
	SunLight light;
	GUI* GUI;
} Scene;

//Create a scene
Scene* scene_create(char* name);

//Destroy a scene
void scene_destroy(Scene* scene);

//Destroy the content of a scene
void scene_destroy_content(Scene* scene);

//Setup all the scripts
void scene_setup(Scene* scene);

//Run all the scripts
void scene_run(Scene* scene);

//Run all the scene objects
void scene_draw(Scene* scene);

//Add a scene objects as a root to a scene
void scene_add_so(Scene* scene, SceneObject* so);

//Remove and destroy a scene objects from a scene
void scene_delete_so(Scene* scene, SceneObject* so);

//Attach a root scene object to another scene object
void scene_attach_so(Scene* scene, SceneObject* child, SceneObject* parent);

//Detach a scene object from his parents and change it as a root
void scene_detach_so(Scene* scene, SceneObject* so);

#endif /* SCENE_H_ */
