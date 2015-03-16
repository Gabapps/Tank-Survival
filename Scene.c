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
		new_scene->sceneObjects = (SceneObject*)malloc(50*sizeof(SceneObject*));
		if(new_scene->sceneObjects == NULL)
		{
			fprintf(stderr, "Error during the allocation of sceneObjects in the function scene_create");
			return NULL;
		}
		new_scene->count = 0;
		new_scene->script = NULL;
		camera_init(new_scene->camera);
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
	free(scene);
}


/**
 * \fn void scene_setup(Scene* scene)
 * \brief Setup the scene
 *
 * \param scene The scene to setup
 */
/*
void scene_setup(Scene* scene)
{
	scene->script->setup;
}
*/


/**
 * \fn void scene_run(Scene* scene)
 * \brief Run the scene
 *
 * \param scene The scene to run
 */
/*
void scene_run(Scene* scene)
{

}
*/

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

	if(scene->count >= 49)
	{
		scene->sceneObjects = (SceneObject*)realloc((SceneObject*)scene->sceneObjects, 200 * sizeof(SceneObject*));
	}

	scene->sceneObjects[scene->count] = so;
	scene->count++;
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
	//Retire so dans le tableau sceneObject de la structure scene

	int temp = -1;

	temp = scene_find_so(scene, so);

	if(temp == -1)
	{
		fprintf(stderr, "Error during the research of sceneObjects in the function scene_delete_so");
		return 0;
	}
	else
	{
		if(scene->count <= 49)
		{
			scene->sceneObjects = (SceneObject*)realloc((SceneObject*)scene->sceneObjects, 50 * sizeof(SceneObject*));
		}

		free(scene->sceneObjects[temp]);
		scene->sceneObjects[temp] = scene->sceneObjects[scene->count];
		scene->count--;
	}
}


/**
 * \fn SceneObject* scene_find_so(Scene* scene, SceneObject* so)
 * \brief Find the index of a sceneObject in the scene
 *
 * \param scene The scene
 * \param so The sceneObject to find in the scene
 */
int scene_find_so(Scene* scene, SceneObject* so)
{
	//Recherche so dans le tableau sceneobject de la structure scene
	int i;

	for(i=0; i<scene->count; i++)
	{
		if(scene->sceneObjects == so)
		{
			return i;
		}
	}

	return -1;
}
