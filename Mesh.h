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

//Create a mesh
Mesh* mesh_create();

//Load a mesh from .obj file
int mesh_load_from_obj(Mesh* mesh, char* filename);

//Load mesh into his Virtual Buffer Object (VBO)
void mesh_load_vbo(Mesh* mesh);

//Load a 2D canvas for the GUI
void mesh_load_canvas();

//Return the 2D canvas for the GUI
Mesh* mesh_get_canvas();

//Create a mesh for a TextView GUI Widget
Mesh* mesh_get_text_view_canvas(const char* text);

//Destroy a mesh
void mesh_free(Mesh* mesh);

#endif /* MESH_H_ */
