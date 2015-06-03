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

/*!
 * \struct Mesh
 * Mesh structure
 */
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

/**
 * \fn Mesh* mesh_create()
 * \brief Create a mesh
 */
Mesh* mesh_create();

/**
 * \fn int mesh_load_from_obj(Mesh* mesh, char* filename)
 * \brief Load a mesh from .obj file
 *
 * \param [out] mesh The mesh
 * \param [in] filename The path to the file
 */
int mesh_load_from_obj(Mesh* mesh, char* filename);

/**
 * \fn void mesh_load_vbo(Mesh* mesh)
 * \brief Load mesh into his Virtual Buffer Object (VBO)
 *
 * \param [in] mesh The mesh
 */
void mesh_load_vbo(Mesh* mesh);

/**
 * \fn void mesh_load_canvas()
 * \brief Load a 2D canvas for the GUI
 */
void mesh_load_canvas();

/**
 * \fn Mesh* mesh_get_canvas()
 * \brief Return the 2D canvas for the GUI
 *
 * \return the 2D canvas for the GUI
 */
Mesh* mesh_get_canvas();

/**
 * \fn Mesh* mesh_get_text_view_canvas(const char* text);
 * \brief Create a mesh for a TextView GUI Widget
 *
 * \param [in] text The text
 *
 * \return the mesh related to the text
 */
Mesh* mesh_get_text_view_canvas(const char* text);

/**
 * \fn void mesh_free(Mesh* mesh);
 * \brief Destroy a mesh
 *
 * \param [in] mesh The mesh
 */
void mesh_free(Mesh* mesh);

#endif /* MESH_H_ */
