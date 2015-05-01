/*
 * Wall.h
 *
 *  Created on: 22 avr. 2015
 *      Author: max
 */

#ifndef SCRIPTS_WALL_H_
#define SCRIPTS_WALL_H_

typedef struct Wall {
	define_script(Wall);
	int dest; //mur destructible ?
	int life;
}Wall;

void wall_setup(Wall* wall, SceneObject* so) {
	so->mesh = ressources_get_mesh(MESH_WALL);
	so->shader = ressources_get_shader(SHADER_TEXTURE);
	so->texture = ressources_get_texture(TEXTURE_WALL);
	so->collider = collider_create(0.5, 0.5);
	wall->life=100;
}

void wall_run(Wall* wall, SceneObject* so) {

}

#endif /* SCRIPTS_WALL_H_ */
