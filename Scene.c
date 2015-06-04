/*
 * Scene.c
 *
 *  Created on: 16 mars 2015
 *      Author: Nicolas
 */

#include "Scene.h"

list_so* so_to_destroy;


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
		camera_init(&(new_scene->camera));
		new_scene->GUI = NULL;
		sound_setup_listener(new_scene->camera.pos, new_scene->camera.dir);
	}
	return new_scene;
}



void scene_destroy(Scene* scene)
{
	scene_destroy_content(scene);
	free(scene->name);
	free(scene->script);
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

	node_sound *iterator2 = sounds->root;
	while(iterator2 != NULL) {
		Sound* temp = iterator2->value;
		iterator2 = iterator2->next;

		alSourceStop(temp->source);
		sound_remove(temp, sounds);
		//sound_destroy(temp);
	}

	free(scene->sceneObjects);
	scene->sceneObjects = list_so_create();
}


void scene_setup(Scene* scene)
{
	if(so_to_destroy) list_so_free(so_to_destroy);
	so_to_destroy = list_so_create();

	if(scene->script!=NULL)
		scene->script->setup(scene->script, NULL);

	node_so *iterator = scene->sceneObjects->root;
	while(iterator != NULL) {
		so_setup(iterator->value);
		iterator = iterator->next;
	}

	sound_add("Audio/musique.ogg", sounds, 1, 0.7);
	//	addSound("Audio/musique.ogg", scene->sounds, 1, 1);
}



void scene_run(Scene* scene)
{
	if(scene->script!=NULL)
		scene->script->run(scene->script, NULL);

	if(scene->GUI && scene->GUI->current_root) {
		GUI_run(scene->GUI);
	}

	node_so *iterator = so_to_destroy->root;
	while(iterator != NULL) {
		so_destroy(iterator->value);
		list_so_delete(scene->sceneObjects, iterator->value, 1);
		node_so* temp = iterator;
		iterator = iterator->next;
		if(temp) list_so_delete(so_to_destroy, temp->value, 0);
	}

	iterator = scene->sceneObjects->root;
	while(iterator != NULL) {
		so_run(iterator->value);
		iterator = iterator->next;
	}
	sounds_play(sounds);
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


void scene_add_so(Scene* scene, SceneObject* so)
{
	//Ajoute so dans le tableau sceneObject de la structure scene
	if(so->transform.parent == NULL)
		list_so_put(scene->sceneObjects, so);
	else printf("Warning : Can't add child sceneObject %s to scene, it must be a root\n", so->name);
}



void scene_delete_so(Scene* scene, SceneObject* so)
{
	list_so_put(so_to_destroy, so);
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
