
/*
 * ressources.c
 *
 *  Created on: 30 mars 2015
 *      Author: ethel
 */
#include "Ressources.h"

void ressources_init(){

	Ressource.meshes = list_mesh_create();
	Ressource.shaders = list_shader_create();
	Ressource.textures = list_texture_create();
}

void ressources_load(){
	FILE * f;
	int count_1;
	int count_2;
	int count_3;
	char path[40] = "Scenes/";
	strcat(path, Game.scene->name);
	strcat(path, ".scene");
	f = fopen(path, "r");
	if (f == NULL)
	{
		printf("Impossible d'ouvrir le fichier test.txt");
	}else{
		int i;
		char path[40];
		fscanf(f, "%d %d %d\n", &count_1, &count_2, &count_3);

		//importation des shaders du fichier dans la liste Ressource.shaders

		for(i=0;i<count_1;i++){
			char path_shaders_vert[40];
			char path_shaders_fragment[40];

			fgets(path, 40, f);
			path[strlen(path)-1]=0;
			strcpy(path_shaders_vert,path);
			strcat(path_shaders_vert,".vert");
			strcpy(path_shaders_fragment,path);
			strcat(path_shaders_fragment,".frag");
			Shader *shader = shader_create(path_shaders_vert,path_shaders_fragment);
			shader_load(shader);
			list_shader_put(Ressource.shaders, shader);
		}

		//importation des meshes du fichier dans la liste Ressource.meshes
		for(i=0;i<count_2;i++){
			fgets(path, 40, f);
			path[strlen(path)-1]=0;
			Mesh *mesh = mesh_create();
			mesh_load_from_obj(mesh, path);
			list_mesh_put(Ressource.meshes, mesh);
		}


		for(i=0;i<count_3;i++){
			//importation des textures du fichier dans la liste Ressource.textures
			fgets(path, 40, f);
			path[strlen(path)-1]=0;
			Texture *texture = texture_create(path);
			texture_from_BMP(texture);
			texture_load(texture);
			list_texture_put(Ressource.textures, texture);
		}

	}
}

Shader* ressources_get_shader(Shader_ID a){
	node_shader *iterator = Ressource.shaders->root;

	int i;
	for(i=0;i<a;i++){
		if(iterator==NULL) return NULL;
		iterator = iterator->next;
	}
	return iterator->value;
}


Mesh* ressources_get_mesh(Mesh_ID a){
	node_mesh *iterator = Ressource.meshes->root;

		int i;
		for(i=0;i<a;i++){
			if(iterator==NULL) return NULL;
			iterator = iterator->next;
		}
		return iterator->value;
}


Texture* ressources_get_texture(Texture_ID a){
	node_texture *iterator = Ressource.textures->root;

		int i;
		for(i=0;i<a;i++){
			if(iterator==NULL) return NULL;
			iterator = iterator->next;
		}
		return iterator->value;
}

