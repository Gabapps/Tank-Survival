/*
 * Tank.h
 *
 *  Created on: 17 mars 2015
 *      Author: Gabriel
 */

#ifndef SCRIPTS_TANK_H_
#define SCRIPTS_TANK_H_

#include <string.h>
#include "Items.h"

#define MAX_PLAYER 4

typedef struct Tank {
	define_script(Tank);
	float speed;
	int life;
	int player;
	int damage;
} Tank;

Tank* tanks[MAX_PLAYER];

const int totallife = 150;

void tank_setup(Tank* tank, SceneObject* so) {

	so->mesh = ressources_get_mesh(MESH_TANK);
	so->shader = ressources_get_shader(SHADER_TEXTURE);
	so->texture = ressources_get_texture(TEXTURE_TANK);
	so->collider = collider_create(0.27, 0.45); //0.49
	tank->speed=1;
	tank->damage = 50;
	tanks[tank->player] = tank;
	tank->life=totallife;
}

void tank_run(Tank* tank, SceneObject* so) {
	vec3 v = {tank->speed,0,0};
	vec3_scale(v,v,Time.deltaTime);

	Item* item = NULL;

	//On sauvegarde l'état avant transformation
	Transform backup = so->transform;

	//On bouge
	if(input_keypressed_index(5*tank->player+3)) {
		transform_rotateY(&(so->transform), -Time.deltaTime);
	}
	if(input_keypressed_index(5*tank->player+2)) {
		transform_rotateY(&(so->transform), Time.deltaTime);
	}
	if(input_keypressed_index(5*tank->player)) {
		transform_translate(&(so->transform), v);
	}
	else if(input_keypressed_index(5*tank->player+1)) {
		vec3_scale(v,v,-0.7f);
		transform_translate(&(so->transform), v);
	}

	node_so *iterator = Game.scene->sceneObjects->root;
	while(iterator != NULL) //Tant qu'on a pas testé tous les so de la scene
	{
		// Si le so vérifié a un collider et que ce n'est pas le tank lui-même
		if(iterator->value->collider && iterator->value!=so) {
			SceneObject *collision_so = so_collision(so, iterator->value);
			if(collision_so!= NULL)
			{
				if(strcmp(collision_so->name, "Tank") == 0)
				{
					//On annule le mouvement
					transform_copy(&(so->transform), &backup);
				}
				else if(strcmp(collision_so->name, "Wall") == 0)
				{
					//On annule le mouvement
					transform_copy(&(so->transform), &backup);
				}
				else if(strcmp(collision_so->name, "Item") == 0)
				{
					//Collision avec un item
					item = (Item*)collision_so->scripts->root->value;
					if(item->laser) {
						SceneObject* laser = so_create("Laser", transform_xyz_no_parent(0.65,0.35,0));
						Item* itemlaser = (Item*)malloc(sizeof(Item));
						itemlaser->setup = item_setup;
						itemlaser->run = item_run;
						itemlaser->laser = 2;

						laser->shader = ressources_get_shader(SHADER_TEXTURE);
						laser->mesh = ressources_get_mesh(MESH_ITEMS_LASER);
						laser->texture = ressources_get_texture(TEXTURE_RED);

						so_add_script(laser, (Script*)itemlaser);

						so_add_child(so, laser);
						so_setup(laser);
					}
					else if(item->speed > 0 || item->fire > 0) {
						tank->speed += item->speed;
						tank->damage += item->fire;
					}
					else {
						int i;
						for(i=0; i < MAX_PLAYER; i++) {
							if(i!=tank->player) {
								if(tanks[i]->speed >= 0.8)
								{
									tanks[i]->speed += item->speed;
								}
								if(tanks[i]->damage >= 20)
								{
									tanks[i]->damage += item->fire;
								}
							}
						}
					}
					item->destroying = 1;
				}
			}
		}
		iterator = iterator->next;
	}
	if(tank->life > 0 && tank->life < totallife/2) {
		so->mesh = ressources_get_mesh(MESH_TANK_DAMAGED);
		so->texture = ressources_get_texture(TEXTURE_TANK_DAMAGED);
	}

	if(tank->life <= 0) {
		tank->life=0;
		so->mesh = ressources_get_mesh(MESH_TANK_DEAD);
		so->texture = ressources_get_texture(TEXTURE_TANK_DEAD);
		so_rm_script(so, (Script*)tank);
	}

}

#endif /* SCRIPTS_TANK_H_ */
