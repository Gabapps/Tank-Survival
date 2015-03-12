/*
 * SceneObject.c
 *
 *  Created on: 11 mars 2015
 *      Author: Gabriel
 */

#include "SceneObject.h"

SceneObject* so_create(char* name, Transform t) {
	SceneObject* so = (SceneObject*)malloc(sizeof(SceneObject));
	so->transform=t;
	so->name=name;
	so->mesh=NULL;
	so->shader=NULL;
	so->scripts=NULL;
	so->count_script=0;
	return so;
}

void so_detroy(SceneObject* so) {
	free(so->name);
	free(so);
}

SceneObject* so_duplicate(SceneObject* so, char* name, Transform t) {
	SceneObject* new_so = (SceneObject*)malloc(sizeof(SceneObject));
	*new_so=*so;
	new_so->transform=t;
	return new_so;
}

void so_init(SceneObject* so, Scene* sc) {
	int i;
	for(i=0; i<so->count_script; i++)
		so->scripts[i].setup(&(so->scripts[i]), so, sc);
}

void so_run(SceneObject* so, Scene* sc) {
	int i;
	for(i=0; i<so->count_script; i++)
		so->scripts[i].run(&(so->scripts[i]), so, sc);
}

void so_draw(SceneObject* so, Camera* cam) {
	//transform_refresh_matrix(so->transform);

	glUseProgram(so->shader->program); // On verouille le shader

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, mesh_get_vertices(so->mesh));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, mesh_get_normals(so->mesh));
	glEnableVertexAttribArray(1);

	glUniformMatrix4fv(glGetUniformLocation(so->shader->program, "M"), 1, GL_FALSE, mat4x4_ptr(so->transform.matrix));
	glUniformMatrix4fv(glGetUniformLocation(so->shader->program, "V"), 1, GL_FALSE, mat4x4_ptr(cam->perspective_matrix));
	glUniformMatrix4fv(glGetUniformLocation(so->shader->program, "P"), 1, GL_FALSE, mat4x4_ptr(cam->transform.matrix));
	//glUniform3fv(glGetUniformLocation(so->shader->program, "target"), 1,pos);

	glDrawArrays(GL_TRIANGLES, 0, so->mesh->f*3);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glUseProgram(0);
}
