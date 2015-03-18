/*
 * Scene.c
 *
 *  Created on: 16 mars 2015
 *      Author: Nicolas
 */

#include "Scene.h"

/**
 * \fn Scene* scene_create()
 * \brief Create Scene
 *
 * \param name The name of the scene
 */
Scene* scene_create(char* name)
{
	Scene* new_scene = (Scene*)malloc(sizeof(Scene));
	if(new_scene == NULL)
	{
		fprintf(stderr, "Error during the allocation of the scene in the function scene_create");
		return NULL;
	}
	else
	{
		new_scene->name = name;
		new_scene->sceneObjects = list_so_create();
		new_scene->script = NULL;
		camera_init(&(new_scene->camera));
	}
	return new_scene;
}


/**
 * \fn void scene_destroy(Scene* scene)
 * \brief Destroy the scene
 *
 * \param scene The scene to destroy
 */
void scene_destroy(Scene* scene)
{
	free(scene->name);
	// TODO : add destroy list
	free(scene);
}


/**
 * \fn void scene_setup(Scene* scene)
 * \brief Setup the scene
 *
 * \param scene The scene to setup
 */

void scene_setup(Scene* scene)
{
	scene->script->setup(scene->script, NULL);
}



/**
 * \fn void scene_run(Scene* scene)
 * \brief Run the scene
 *
 * \param scene The scene to run
 */

void scene_run(Scene* scene)
{
	scene->script->run(scene->script, NULL);
}


/**
 * \fn void scene_add_so(Scene* scene, SceneObject* so)
 * \brief Add a sceneObject to the scene
 *
 * \param scene The scene
 * \param so The sceneObject to add in the scene
 */
void scene_add_so(Scene* scene, SceneObject* so)
{
	//Ajoute so dans le tableau sceneObject de la structure scene

	list_so_put(scene->sceneObjects, so);
}


/**
 * \fn int scene_delete_so(Scene* scene, SceneObject* so)
 * \brief Delete a sceneObject from the scene
 *
 * \param scene The scene
 * \param so The sceneObject to delete of the scene
 *
 * return The deleted sceneObject
 */
int scene_delete_so(Scene* scene, SceneObject* so)
{
	return list_so_delete(scene->sceneObjects, so, 1);;
}


/**
 * \fn SceneObject* scene_find_so(Scene* scene, SceneObject* so)
 * \brief Find the index of a sceneObject in the scene
 *
 * \param scene The scene
 * \param so The sceneObject to find in the scene
 */
/*int scene_find_so(Scene* scene, SceneObject* so)
{
	//Recherche so dans le tableau sceneobject de la structure scene

	node_so* iterator = scene->sceneObjects->root;

	return -1;
}*/
