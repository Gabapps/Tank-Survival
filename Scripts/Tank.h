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
	tank->speed=1;
}

void tank_run(Tank* tank, SceneObject* so) {
	vec3 v = {0,0,-tank->speed};
	vec3_scale(v,v,Time.deltaTime);

	if(input_keypressed("P1_up")) {
		transform_translate(&(so->transform), v);
	}
	/*if(input_keypressed("P1_up")) {
		transform_rotateY(&(so->transform), Time.deltaTime);
	}*/
}

#endif /* SCRIPTS_TANK_H_ */
