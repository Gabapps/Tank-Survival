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
		new_scene->light = sunlight_default();
		new_scene->sounds = initSoundList();
		camera_init(&(new_scene->camera));
		new_scene->GUI = NULL;
		setupListener(new_scene->camera.pos, new_scene->camera.dir);
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
	scene_destroy_content(scene);
	free(scene->name);
	free(scene->script);
	free(scene->sounds);
	free(scene);
}


void scene_destroy_content(Scene* scene) {
	if(scene->GUI && scene->GUI->current_root) {
		GUI_destroy(scene->GUI);
	}

	node_so *iterator = scene->sceneObjects->root;
	while(iterator != NULL) {
		so_destroy(iterator->value);
		iterator = iterator->next;
	}

	node_sound *iterator2 = scene->sounds->root;
	while(iterator2 != NULL) {
		alSourceStop(iterator2->value->source);
		iterator2 = iterator2->next;
	}

	free(scene->sceneObjects);
	scene->sceneObjects = list_so_create();

	free(scene->sounds);
	scene->sounds = initSoundList();
}


/**
 * \fn void scene_setup(Scene* scene)
 * \brief Setup the scene
 *
 * \param scene The scene to setup
 */

void scene_setup(Scene* scene)
{
	if(scene->script!=NULL)
		scene->script->setup(scene->script, NULL);

	node_so *iterator = scene->sceneObjects->root;
	while(iterator != NULL) {
		so_setup(iterator->value);
		iterator = iterator->next;
	}

	//addSound("Audio/musique.ogg", scene->sounds, 1, 1);
}



/**
 * \fn void scene_run(Scene* scene)
 * \brief Run the scene
 *
 * \param scene The scene to run
 */

void scene_run(Scene* scene)
{
	if(scene->script!=NULL)
		scene->script->run(scene->script, NULL);

	if(scene->GUI && scene->GUI->current_root) {
		GUI_run(scene->GUI);
	}

	node_so *iterator = scene->sceneObjects->root;
	while(iterator != NULL) {
		so_run(iterator->value);
		iterator = iterator->next;
	}
	playSounds(scene->sounds);
}

void scene_draw(Scene* scene) {

	glEnable(GL_BLEND);

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if(scene->GUI && scene->GUI->current_root) {
		GUI_draw(scene->GUI);
	}

	camera_refresh_matrices(&(scene->camera));
	glDisable(GL_BLEND);
	node_so *iterator = scene->sceneObjects->root;
	while(iterator != NULL) {
		so_draw(iterator->value, &(scene->camera), &(scene->light));
		iterator = iterator->next;
	}
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
	if(so->transform.parent == NULL)
		list_so_put(scene->sceneObjects, so);
	else printf("Warning : Can't add child sceneObject %s to scene, it must be a root\n", so->name);
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
	return list_so_delete(scene->sceneObjects, so, 1);
}

void scene_attach_so(Scene* scene, SceneObject* child, SceneObject* parent) {
	if(child->transform.parent == NULL) {
		list_so_delete(scene->sceneObjects, child, 0);
		so_add_child(parent, child);
	}
	else {
		printf("Warning : You're trying to attach a sceneObject %s that is not a root\n"
				"Use so_add_child instead\n", child->name);
	}
}

void scene_detach_so(Scene* scene, SceneObject* so) {
	if(so->transform.parent) {
		transform_to_world_coord(&(so->transform));
		transform_rm_child(so->transform.parent, &(so->transform));
		so->transform.parent = NULL;
		scene_add_so(scene, so);
	}
	else {
		printf("Warning : You're trying to detach a sceneObject %s is already a root\n", so->name);
	}
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
