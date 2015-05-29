/*
 * Items.h
 *
 *  Created on: 17 mai 2015
 *      Author: Nicolas
 */

#ifndef SCRIPTS_ITEMS_H_
#define SCRIPTS_ITEMS_H_

#include "../Script.h"
#include "../SceneObject.h"

#include <time.h> /* srand(), rand */

#define NB_ITEMS 5

typedef struct Item{
	define_script(Item);
	float speed;
	int fire;
	int laser;
	int destroying;
	float time;
	float scale;
	Mesh* mesh;
}Item;


void item_setup(Item* item, SceneObject* so) {
	item->time = 0;
	item->scale = 1;
	item->destroying = 0;
	item->mesh = so->mesh;
}

void item_run(Item* item, SceneObject* so) {
	//Rotation de l'item
	if(item->laser<2) transform_rotateY(&(so->transform), Time.deltaTime);

	if(item->destroying) {
		free(so->collider);
		so->collider = NULL;
		so->mesh = item->mesh;
		item->scale+=4*Time.deltaTime;
		transform_scale(&(so->transform), 1/item->scale, 1/item->scale, 1/item->scale);
		if(item->scale > 5) {
			if(so->transform.parent) scene_detach_so(Game.scene, so);
			scene_delete_so(Game.scene, so);
		}
	}
	else {
		item->time+=Time.deltaTime;
		if(item->time >= 10 && item->time < 15) {
			int visible = (int)(item->time * 3)%2;
			so->mesh = (visible ? item->mesh : NULL);
		}
		if(item->time >= 15)
		{
			if(so->transform.parent) {
				scene_detach_so(Game.scene, so);
			}
			scene_delete_so(Game.scene, so);
			item->time = 0;
		}
	}
}

void activ_items(float x, float y)
{
	//Active les items
	//Si aucun items n'a été prit, replacer nouveaux items sur la maps
	Transform t = transform_xyz_no_parent(x,0,y);
	SceneObject* item = so_create("Item", t);
	item->shader = ressources_get_shader(SHADER_TEXTURE);

	Item* item_struct = (Item*)malloc(sizeof(Item));
	item_struct->setup = item_setup;
	item_struct->run = item_run;

	//Choisir un item avec un random
	int random_item;
	random_item = rand()%(NB_ITEMS);
	switch(random_item){
	case 0 :
		item->mesh = ressources_get_mesh(MESH_ITEMS_SPEED_M);
		item->texture = ressources_get_texture(TEXTURE_GREEN);
		item->collider = collider_create(0.5, 0.5);
		item_struct->fire = 0;
		item_struct->speed = 1;
		item_struct->laser = 0;
		break;
	case 1 :
		item->mesh = ressources_get_mesh(MESH_ITEMS_SPEED_L);
		item->texture = ressources_get_texture(TEXTURE_RED);
		item->collider = collider_create(0.5, 0.5);
		item_struct->fire = 0;
		item_struct->speed = -0.5;
		item_struct->laser = 0;
		break;
	case 2 :
		item->mesh = ressources_get_mesh(MESH_ITEMS_FIRE_M);
		item->texture = ressources_get_texture(TEXTURE_GREEN);
		item->collider = collider_create(0.5, 0.5);
		item_struct->fire = 50;
		item_struct->speed = 0;
		item_struct->laser = 0;
		break;
	case 3 :
		item->mesh = ressources_get_mesh(MESH_ITEMS_FIRE_L);
		item->texture = ressources_get_texture(TEXTURE_RED);
		item->collider = collider_create(0.5, 0.5);
		item_struct->fire = -50;
		item_struct->speed = 0;
		item_struct->laser = 0;
		break;
	default :
		item->mesh = ressources_get_mesh(MESH_ITEMS_LASER_M);
		item->texture = ressources_get_texture(TEXTURE_GREEN);
		item->collider = collider_create(0.5, 0.5);
		item_struct->fire = 0;
		item_struct->speed = 0;
		item_struct->laser = 1;
	}

	so_add_script(item, (Script*)item_struct);
	so_setup(item);
	scene_add_so(Game.scene, item);
}

#endif /* SCRIPTS_ITEMS_H_ */
