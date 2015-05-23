/*
 * ressources.h
 *
 *  Created on: 30 mars 2015
 *      Author: ethel
 */

#ifndef RESSOURCES_H_
#define RESSOURCES_H_
#include "Game.h"

typelist(mesh, Mesh*);
typelist(shader, Shader*);
typelist(texture, Texture*);

typedef enum {MESH_TANK, MESH_TANK_DAMAGED, MESH_TANK_DEAD, MESH_WALL, MESH_MISSILE, MESH_GROUND, MESH_EXPLOSION,  MESH_ITEMS_SPEED_M, MESH_ITEMS_SPEED_L, MESH_ITEMS_FIRE_M, MESH_ITEMS_FIRE_L} Mesh_ID;
typedef enum {SHADER_GUI, SHADER_TEXTURE, SHADER_NOTEXTURE} Shader_ID;
typedef enum {TEXTURE_TANK, TEXTURE_TANK_DEAD, TEXTURE_WALL, TEXTURE_BULLET, TEXTURE_GROUND, TEXTURE_EXPLOSION} Texture_ID;
//TEXTURE_ITEMS_SPEED_M, TEXTURE_ITEMS_SPEED_L, TEXTURE_ITEMS_FIRE_M, TEXTURE_ITEMS_FIRE_L

typedef struct Ressources{
	char* name; //Nom de l'objet
	list_mesh* meshes; //Tableau contenant les différents meshs
	list_shader* shaders; //Tableau contenant les différents shaders
	list_texture* textures;//Tableau contenant les différentes textures
} Ressources;

Ressources Ressource;


void ressources_init();
void ressources_load();
Shader* ressources_get_shader(Shader_ID a);
Mesh* ressources_get_mesh(Mesh_ID a);
Texture* ressources_get_texture(Texture_ID a);

#endif /* RESSOURCES_H_ */
