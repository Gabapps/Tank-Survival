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
} Tank;

void tank_setup(Tank* tank, SceneObject* so) {

	so->mesh = ressources_get_mesh(MESH_TANK);
	so->shader = ressources_get_shader(SHADER_TEXTURE);
	so->texture = ressources_get_texture(TEXTURE_TANK);
	tank->speed=1;
}

void tank_run(Tank* tank, SceneObject* so) {
	vec3 v = {tank->speed,0,0};
	vec3_scale(v,v,Time.deltaTime);

	if(input_keypressed("P1_right")) {
		transform_rotateY(&(so->transform), -Time.deltaTime);
	}
	if(input_keypressed("P1_left")) {
			transform_rotateY(&(so->transform), Time.deltaTime);
	}
	if(input_keypressed("P1_up")) {
		transform_translate(&(so->transform), v);
	}
	else if(input_keypressed("P1_down")) {
		vec3_scale(v,v,-0.7f);
		transform_translate(&(so->transform), v);
	}

}

#endif /* SCRIPTS_TANK_H_ */
