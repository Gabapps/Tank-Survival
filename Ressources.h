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


typedef enum {MESH_TANK, MESH_TANK_DAMAGED, MESH_TANK_DEAD, MESH_WALL, MESH_ANTICHAR, MESH_MISSILE, MESH_GROUND, MESH_SKY, MESH_EXPLOSION, MESH_ITEMS_SPEED_M, MESH_ITEMS_SPEED_L, MESH_ITEMS_FIRE_M, MESH_ITEMS_FIRE_L, MESH_ITEMS_LASER_M, MESH_ITEMS_LASER} Mesh_ID;

typedef enum {SHADER_GUI, SHADER_TEXTURE, SHADER_NOTEXTURE, SHADER_SKYBOX} Shader_ID;

typedef enum {TEXTURE_TANK, TEXTURE_TANK_DAMAGED, TEXTURE_TANK_DEAD, TEXTURE_WALL, TEXTURE_ANTICHAR, TEXTURE_BULLET, TEXTURE_GROUND, TEXTURE_SKY, TEXTURE_EXPLOSION, TEXTURE_GREEN, TEXTURE_RED} Texture_ID;

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
