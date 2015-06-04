/**
 * @file Ressources.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 30 Mar 2015
 * @brief The global Ressource structure centralizes the meshes, textures and shaders in chained lists.
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

//Initialize ressources lists
void ressources_init();

//Load all meshes, textures and shaders from the "Scenes/{Name of the current scene).scene" file
void ressources_load();

//Get a shader from ID
Shader* ressources_get_shader(Shader_ID a);

//Get a mesh from ID
Mesh* ressources_get_mesh(Mesh_ID a);

//Get a texture from ID
Texture* ressources_get_texture(Texture_ID a);

#endif /* RESSOURCES_H_ */
