/*
 * Mesh.h
 *
 *  Created on: 5 févr. 2015
 *      Author: Gabriel
 */

#ifndef MESH_H_
#define MESH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	float* vertices; // x0 y0 z0 x1 y1 z1
	float* normals; //
	int* triangles_id;
	int* normals_id;
	int v,vn,f;
} Mesh;

Mesh* mesh_create();

int mesh_load_from_obj(Mesh* mesh, char* filename);

void mesh_send_to_shader(Mesh* mesh);

float* mesh_get_vertices(Mesh* mesh);

float* mesh_get_normals(Mesh* mesh);

void mesh_free(Mesh* mesh);

#endif /* MESH_H_ */
