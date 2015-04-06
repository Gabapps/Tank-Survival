/*
 * Bullet.h
 *
 *  Created on: 4 avr. 2015
 *      Author: ethel
 */

#ifndef SCRIPTS_BULLET_H_
#define SCRIPTS_BULLET_H_

#include "../Script.h"

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
	bullet->active =0;
	bullet->time = 0;
}

void bullet_run(Bullet* bullet, SceneObject* so){
	Tank* tank = bullet->fromtank->scripts->root->value;
	vec3 v = {bullet->speed,0,0};
	vec3_scale(v,v,Time.deltaTime);
	if(bullet->active == 0){
		so->transform = bullet->fromtank->transform;
	}
	else bullet->time+= Time.deltaTime;
	if(bullet->time>2) {
		bullet->active =0;
		so->transform = bullet->fromtank->transform;
		bullet->speed = 0;
		bullet->time = 0;

	}

	//so->transform = tank->transform; Avec ça on suit bien la pos du tank mais on ne peut pas tirer car on bloque la position de la balle

	if(input_keypressed_index(5*tank->player+4)){
		bullet->speed =15;
		bullet->active=1;

	}
	transform_translate(&(so->transform), v);
}



#endif /* SCRIPTS_BULLET_H_ */
