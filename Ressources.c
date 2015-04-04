
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
	f = fopen("ressources.scene", "r");
	if (f == NULL)
	{
		printf("Impossible d'ouvrir le fichier test.txt");
	}else{
		int i;
		fscanf(f, "%d %d %d\n", &count_1, &count_2, &count_3);
		if(count_1 != 0){
			//importation des shaders du fichier dans la liste Ressource.shaders

			for(i=0;i<=count_1;i++){
				char* path_shaders;
				fgets(path_shaders, 40, f);
				Shader *shader = shader_create(strcat(path_shaders,".vert"),strcat(path_shaders,".frag"));
				shader_load(shader);
				list_shader_put(Ressource.shaders, shader);
			}
		}
		if(count_2 != 0){
			//importation des meshes du fichier dans la liste Ressource.meshes
			for(i=0;i<=count_2;i++){
				char* path_meshes;
				fgets(path_meshes, 40, f);
				Mesh *mesh = mesh_create();
				mesh_load_from_obj(mesh, path_meshes);
				list_mesh_put(Ressource.meshes, mesh);
			}
		}
		if(count_3 != 0){
			for(i=0;i<=count_2;i++){
				//importation des textures du fichier dans la liste Ressource.textures
				char* path_textures;
				fgets(path_textures, 40, f);
				Texture *texture = texture_create("path_textures");
				texture_from_BMP(texture);
				texture_load(texture);
				list_mesh_put(Ressource.textures, texture);
			}
		}
	}
}

Shader* ressources_get_Shaderfromlist(int a){
	node_shader *iterator = Ressource.shaders->root;

	while(iterator->next != NULL){
		int i;
		for(i=0;i<a;i++){
			iterator = iterator->next;
		}
		return iterator->value;
	}
}


Mesh* ressources_get_MeshfromList(int a){
	node_mesh *iterator = Ressource.meshes->root;

	while(iterator->next != NULL){
		int i;
		for(i=0;i<a;i++){
			iterator = iterator->next;
		}
		return iterator->value;
	}
}


Texture* ressources_get_Texture(int a){
	node_texture *iterator = Ressource.textures->root;

	while(iterator->next != NULL){
		int i;
		for(i=0;i<a;i++){
			iterator = iterator->next;
		}
		return iterator->value;
	}
}

