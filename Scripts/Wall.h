/*
 * Wall.h
 *
 *  Created on: 22 avr. 2015
 *      Author: max
 */

#ifndef SCRIPTS_WALL_H_
#define SCRIPTS_WALL_H_

#include "../Game.h"

typedef struct Wall {
	define_script(Wall);
	int destrutible; //mur destructible ?
	int life;
	Texture_ID texture;
	Mesh_ID mesh;
}Wall;

void wall_setup(Wall* wall, SceneObject* so) {
	so->mesh = ressources_get_mesh(wall->mesh);
	so->shader = ressources_get_shader(SHADER_TEXTURE);
	so->texture = ressources_get_texture(wall->texture);
	so->collider = collider_create(0.5, 0.5);
}

void wall_run(Wall* wall, SceneObject* so) {
	if(wall->destrutible && wall->life <= 0) {
		scene_delete_so(Game.scene, so);
	}
}

#endif /* SCRIPTS_WALL_H_ */
