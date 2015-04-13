/*
 * Tank.h
 *
 *  Created on: 17 mars 2015
 *      Author: Gabriel
 */

#ifndef SCRIPTS_TANK_H_
#define SCRIPTS_TANK_H_

typedef struct Tank {
	define_script(Tank);
	float speed;
	int life;
	int player;
} Tank;

void tank_setup(Tank* tank, SceneObject* so) {

	so->mesh = ressources_get_mesh(MESH_TANK);
	so->shader = ressources_get_shader(SHADER_TEXTURE);
	so->texture = ressources_get_texture(TEXTURE_TANK);
	tank->speed=1;
	tank->life=100;
}

void tank_run(Tank* tank, SceneObject* so) {
	vec3 v = {tank->speed,0,0};
	vec3_scale(v,v,Time.deltaTime);
	int res = 0;

	if(tank->player==0) {
		node_so *iterator = Game.scene->sceneObjects->root;
		while(iterator != NULL) {
			if(so!=iterator->value && iterator->value->collider != NULL) {
				if(so_collision(so, iterator->value)) res=1;
			}
			iterator = iterator->next;
		}
	}
	if(!res) {
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
	}



}

#endif /* SCRIPTS_TANK_H_ */
