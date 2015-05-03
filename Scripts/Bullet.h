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
#include "Wall.h"

typedef struct Bullet{
	define_script(Bullet);
	float speed;
	SceneObject *fromtank;
	Transform startpos;
	int active;
	float time;
	int damage;
}Bullet;

void bullet_reset(Bullet* bullet, SceneObject* so);

void bullet_setup(Bullet* bullet, SceneObject* so){
	bullet->fromtank = so_from_transform(so->transform.parent);
	so->mesh = ressources_get_mesh(MESH_MISSILE);
	so->shader = ressources_get_shader(SHADER_NOTEXTURE);
	//so->texture= ressources_get_texture(TEXTURE_BULLET); //revoir la texture
	bullet->startpos = transform_xyz_no_parent(0.65,0.35,0);
	bullet->startpos.rotation=0;
	so->collider = collider_create(0.03, 0.0012);

	bullet->active = 0;
	transform_copy(&(so->transform), &(bullet->startpos));
	bullet->speed = 0;
	bullet->time = 0;
	bullet->damage = 35;
}

void bullet_run(Bullet* bullet, SceneObject* so){
	Tank* tank = (Tank*) bullet->fromtank->scripts->root->value;

	if(bullet->active)
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
						//Si collision avec un tank, on vire le tank de la scene...
						//scene_delete_so(Game.scene, iterator->value);
						//so_detroy(iterator->value); // /!\"so_detroy" et non "so_destroy"
						//...et on remet le bullet immobile à l'origine

						((Tank*)collision_so->scripts->root->value)->life -= bullet->damage;

						if(((Tank*)collision_so->scripts->root->value)->life <= 0)
						{
								scene_delete_so(Game.scene, iterator->value);
						//		so_detroy(iterator->value);
						}

						transform_origin(&(so->transform));
						bullet->speed = 0;
					}
					else if(strcmp(collision_so->name, "Wall") == 0)
					{
						//le mur est il destructible ?
						if(((Wall*)collision_so->scripts->root->value)->dest == 1)
						{
							((Wall*)collision_so->scripts->root->value)->life -= bullet->damage;

						}

						//faut il en profiter pour enlever le mur ?
						if(((Wall*)collision_so->scripts->root->value)->life <= 0)
						{
							scene_delete_so(Game.scene, iterator->value);
//							so_detroy(iterator->value);
						}

						//On remet le bullet immobile à l'origine
						transform_origin(&(so->transform));
						bullet->speed = 0;
					}
					else if(strcmp(collision_so->name, "Bullet") == 0)
					{
						//Si collision avec un bullet, on ne fait rien pour l'instant
					}
				}
			}

			iterator=iterator->next;
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

	}
	if(bullet->time>2)
	{
		bullet_reset(bullet, so);
	}

}

void bullet_reset(Bullet* bullet, SceneObject* so) {

	bullet->active = 0;
	scene_attach_so(Game.scene, so, bullet->fromtank);
	transform_copy(&(so->transform), &(bullet->startpos));
	bullet->speed = 0;
	bullet->time = 0;
}



#endif /* SCRIPTS_BULLET_H_ */
