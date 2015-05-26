/*
 * Bullet.h
 *
 *  Created on: 4 avr. 2015
 *      Author: ethel
 */

#ifndef SCRIPTS_BULLET_H_
#define SCRIPTS_BULLET_H_

#include "../Script.h"
#include "../SceneObject.h"
#include "Explosion.h"
#include "Wall.h"
#include "../Camera.h"

SceneObject* tank_gagnant = NULL;//scene object pointant sur le tank gagnant

int death_counter;
int end =0;
typedef struct Bullet{
	define_script(Bullet);
	float speed;
	SceneObject *fromtank;
	Transform startpos;
	int active;
	float time;
}Bullet;

void bullet_reset(Bullet* bullet, SceneObject* so);
void bullet_goback(Bullet* bullet, SceneObject* so);
void bullet_explosion(Bullet* bullet, SceneObject* so);

void bullet_setup(Bullet* bullet, SceneObject* so){
	death_counter=0;
	tank_gagnant = NULL;
	bullet->fromtank = so_from_transform(so->transform.parent);
	so->mesh = NULL;
	so->shader = ressources_get_shader(SHADER_TEXTURE);
	so->texture= ressources_get_texture(TEXTURE_BULLET); //revoir la texture
	bullet->startpos = transform_xyz_no_parent(0.65,0.35,0);
	bullet->startpos.rotation=0;
	so->collider = collider_create(0.03, 0.0012);

	bullet->active = 0;
	transform_copy(&(so->transform), &(bullet->startpos));
	bullet->speed = 0;
	bullet->time = 0;
}

void bullet_run(Bullet* bullet, SceneObject* so){
	Tank* tank = NULL;
	if(bullet->fromtank->scripts->root)
		tank = (Tank*) bullet->fromtank->scripts->root->value;
	else {
		bullet_goback(bullet, so);
		so_rm_script(so, (Script*)bullet);
		return;
	}

	if(so->transform.parent == NULL)
	{
		node_so *iterator = Game.scene->sceneObjects->root;
		while(iterator != NULL)
		{
			if(iterator->value->collider && iterator->value!=so && iterator->value!=bullet->fromtank) {
				SceneObject *collision_so = so_collision(so, iterator->value);

				if(collision_so)
				{
					if(strcmp(collision_so->name, "Tank") == 0)
					{
						Tank* tankcol = NULL;
						if(collision_so->scripts->count) tankcol = (Tank*)collision_so->scripts->root->value;
						bullet_explosion(bullet, so);
						//Si collision avec un tank, on vire le tank de la scene...
						//scene_delete_so(Game.scene, iterator->value);
						//so_detroy(iterator->value); // /!\"so_detroy" et non "so_destroy"
						//...et on remet le bullet immobile à l'origine

						if(tankcol) {
							if(collision_so->scripts->count) tankcol->life -= tank->damage; //bullet->damage;

							if(tankcol->life <= 0)
							{
								death_counter++;
								end =1;
								if(death_counter==3){
									tank_gagnant = bullet->fromtank;
								}
							}
						}


						transform_origin(&(so->transform));
						bullet->speed = 0;

						bullet_goback(bullet, so);
						iterator=NULL;

					}
					else if(strcmp(collision_so->name, "Wall") == 0)
					{
						bullet_explosion(bullet, so);
						//le mur est il destructible ?
						if(((Wall*)collision_so->scripts->root->value)->destrutible == 1)
						{
							((Wall*)collision_so->scripts->root->value)->life -= tank->damage;

						}

						//On remet le bullet immobile à l'origine
						bullet_goback(bullet, so);
						iterator=NULL;
					}
					else if(strcmp(collision_so->name, "Bullet") == 0)
					{
						//Si collision avec un bullet, on ne fait rien pour l'instant
					}
				}
			}

			if(iterator) iterator=iterator->next;
		}
	}


	if(bullet->active) {
		bullet->time+= Time.deltaTime;
		vec3 v = {bullet->speed,0,0};
		vec3_scale(v,v,Time.deltaTime);
		transform_translate(&(so->transform), v);
	}

	if(input_keypressed_index(5*tank->player+4) && !bullet->active){
		scene_detach_so(Game.scene, so);
		//		printf("bullet : %f %f %f\n", so->transform.position[0], so->transform.position[1], so->transform.position[2]);
		//		printf("tank : %f %f %f\n", bullet->fromtank->transform.position[0],
		//				bullet->fromtank->transform.position[1],
		//				bullet->fromtank->transform.position[2]);
		bullet->speed =15;
		bullet->active=1;
		so->mesh = ressources_get_mesh(MESH_MISSILE);

	}
	if(bullet->time>2)
	{
		bullet_goback(bullet, so);
		bullet_reset(bullet, so);
	}

}

void bullet_reset(Bullet* bullet, SceneObject* so) {

	bullet->active = 0;
	bullet->time = 0;
}

void bullet_goback(Bullet* bullet, SceneObject* so) {
	if(!so->transform.parent) {
		scene_attach_so(Game.scene, so, bullet->fromtank);
		transform_copy(&(so->transform), &(bullet->startpos));
		bullet->speed = 0;
		so->mesh = NULL;
	}
}

void bullet_explosion(Bullet* bullet, SceneObject* so) {
	Transform t = transform_origin_no_parent();
	transform_copy(&t, &(so->transform));
	SceneObject* exp = so_create("Explosion", t);
	exp->shader = ressources_get_shader(SHADER_TEXTURE);
	exp->mesh = ressources_get_mesh(MESH_EXPLOSION);
	exp->texture = ressources_get_texture(TEXTURE_EXPLOSION);

	Explosion* script = (Explosion*)malloc(sizeof(Explosion));
	script->run = explosion_run;
	script->setup = explosion_setup;

	so_add_script(exp, (Script*)script);
	so_setup(exp);

	scene_add_so(Game.scene, exp);
}


#endif /* SCRIPTS_BULLET_H_ */
