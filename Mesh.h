/*
 * Mesh.h
 *
 *  Created on: 5 févr. 2015
 *      Author: Gabriel
 */

#ifndef MESH_H_
#define MESH_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	float* vertices; // x0 y0 z0 x1 y1 z1
	float* normals; //
	float* uvs;
	int* triangles_id;
	int* normals_id;
	int* uvs_id;
	GLuint vbo;
	int v,vn,f,vt;
} Mesh;

Mesh* mesh_create();

int mesh_load_from_obj(Mesh* mesh, char* filename);

void mesh_load_vbo(Mesh* mesh);

void mesh_load_canvas();

Mesh* mesh_get_canvas();

void mesh_free(Mesh* mesh);

#endif /* MESH_H_ */
