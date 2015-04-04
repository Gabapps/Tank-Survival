/*
 * ressources.h
 *
 *  Created on: 30 mars 2015
 *      Author: ethel
 */

#ifndef RESSOURCES_H_
#define RESSOURCES_H_
#include "List.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"


typelist(mesh, Mesh*);
typelist(shader, Shader*);
typelist(texture, Texture*);

typedef struct Ressources{
	char* name; //Nom de l'objet
	list_mesh* meshes; //Tableau contenant les différents meshs
	list_shader* shaders; //Tableau contenant les différents shaders
	list_texture* textures;//Tableau contenant les différentes textures
} Ressources;

Ressources Ressource;


void ressources_init();
void ressources_load();
Shader* ressources_get_Shader(int a);
Mesh* ressources_get_Mesh(int a);
Texture* ressources_get_Texture(int a);

#endif /* RESSOURCES_H_ */
