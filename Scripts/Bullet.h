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

typedef struct Bullet{
	define_script(Bullet);
	float speed;
	SceneObject *fromtank;
	int active;
	float time;
}Bullet;

void bullet_setup(Bullet* bullet, SceneObject* so){

	so->mesh = ressources_get_mesh(MESH_MISSILE);
	so->shader = ressources_get_shader(SHADER_NOTEXTURE);
	//so->texture= ressources_get_texture(TEXTURE_BULLET); //revoir la texture
	so->transform = bullet->fromtank->transform;
	bullet->speed = 0;
	bullet->active = 0;
	bullet->time = 0;
	so->collider = collider_create(0.2, 0.2);
}

void bullet_run(Bullet* bullet, SceneObject* so){
	Tank* tank = (Tank*) bullet->fromtank->scripts->root->value;
	node_so *iterator = Game.scene->sceneObjects->root;


	if(bullet->active == 0)
	{
		so->transform = bullet->fromtank->transform;
	}
	else bullet->time+= Time.deltaTime;

	if(bullet->active)
	{
		while(iterator != NULL)
		{
			if(iterator->value->collider && iterator->value!=so && iterator->value!=bullet->fromtank) {
				SceneObject *collision_so = so_collision(so, iterator->value);

				if(collision_so)
				{
					if(strcmp(collision_so->name, "Tank") == 0)
					{
						//Si collision avec un tank, on vire le tank de la scene...
						scene_delete_so(Game.scene, iterator->value);
						so_detroy(iterator->value); // /!\"so_detroy" et non "so_destroy"
						//...et on remet le bullet immobile à l'origine
						so->transform = bullet->fromtank->transform;
						bullet->speed = 0;
					}
					else if(strcmp(collision_so->name, "Wall") == 0)
					{
						//Si collision avec un wall, on remet le bullet immobile à l'origine
						so->transform = bullet->fromtank->transform;
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

	if(bullet->time>2)
	{
		bullet->active = 0;
		so->transform = bullet->fromtank->transform;
		bullet->speed = 0;
		bullet->time = 0;

	}

	//so->transform = tank->transform; Avec ça on suit bien la pos du tank mais on ne peut pas tirer car on bloque la position de la balle

	if(input_keypressed_index(5*tank->player+4) && !bullet->active){
		bullet->speed =15;
		bullet->active=1;

	}
	vec3 v = {bullet->speed,0,0};
	vec3_scale(v,v,Time.deltaTime);
	transform_translate(&(so->transform), v);
}



#endif /* SCRIPTS_BULLET_H_ */
