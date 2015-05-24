/*
 * Explosion.h
 *
 *  Created on: 21 mai 2015
 *      Author: Gabriel
 */

#ifndef SCRIPTS_EXPLOSION_H_
#define SCRIPTS_EXPLOSION_H_

#include "../Script.h"
#include "../Game.h"

typedef struct Explosion{
	define_script(Explosion);
	float scale;
}Explosion;

void explosion_run(Explosion* script, SceneObject* so);
void explosion_setup(Explosion* script, SceneObject* so);

void explosion_setup(Explosion* script, SceneObject* so) {
	script->scale = 1;
}

void explosion_run(Explosion* script, SceneObject* so) {
	script->scale+=30*Time.deltaTime;
	if(script->scale >= 7) {
		scene_delete_so(Game.scene, so);
		so->mesh = NULL;
	}
	else  {
		transform_scale(&(so->transform), script->scale, script->scale, script->scale);
	}
}

#endif /* SCRIPTS_EXPLOSION_H_ */
