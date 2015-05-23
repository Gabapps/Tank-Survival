/*
 * SceneObject.c
 *
 *  Created on: 11 mars 2015
 *      Author: Gabriel
 */

#include "SceneObject.h"

//Private functions
void so_draw_one_step(SceneObject* so, Camera* cam, SunLight* light);
void so_destroy_one_step(SceneObject* so);
void so_run_one_step(SceneObject* so);
void so_setup_one_step(SceneObject* so);

list_script scripts_to_destroy = {0, NULL};

SceneObject* so_create(char* name, Transform t) {
	SceneObject* so = (SceneObject*)malloc(sizeof(SceneObject));
	so->transform=t;
	so->name = name;
	so->mesh=NULL;
	so->shader=NULL;
	so->texture=NULL;
	so->scripts=list_script_create();
	so->collider=NULL;
	return so;
}

void so_destroy_one_step(SceneObject* so) {
	free(so->name);
	free(so->scripts);
	free(so);
}
void so_detroy(SceneObject* so) {
	if(so->transform.children->root == NULL) {
		so_destroy_one_step(so);
	}
	else {
		node_tf *iterator = so->transform.children->root;
		while(iterator != NULL) {
			so_detroy(so_from_transform(iterator->value));
			iterator = iterator->next;
		}
		so_destroy_one_step(so);
	}
}

SceneObject* so_duplicate(SceneObject* so, char* name, Transform t) {
	SceneObject* new_so = (SceneObject*)malloc(sizeof(SceneObject));
	new_so->name = name;
	new_so->mesh = so->mesh;
	new_so->shader = so->shader;
	new_so->texture = so->texture;
	new_so->transform = t;
	new_so->scripts = list_script_create();
	new_so->collider = so->collider;
	return new_so;
}

void so_setup_one_step(SceneObject* so) {
	node_script *iterator = so->scripts->root;
	while(iterator != NULL) {
		iterator->value->setup(iterator->value, so);
		iterator = iterator->next;
	}
}

void so_run_one_step(SceneObject* so) {
	node_script *iterator = so->scripts->root;
	while(iterator != NULL) {
		iterator->value->run(iterator->value, so);
		iterator = iterator->next;
	}
	node_script *iterators = scripts_to_destroy.root;
	while(iterators != NULL) {
		list_script_delete(so->scripts, iterators->value, 1);
		iterators = iterators->next;
	}
	scripts_to_destroy.count = 0;
	scripts_to_destroy.root = NULL;
}
void so_setup(SceneObject* so) {
	if(so->transform.children->root == NULL) {
		so_setup_one_step(so);
	}
	else {
		so_setup_one_step(so);
		node_tf *iterator = so->transform.children->root;
		while(iterator != NULL) {
			so_setup(so_from_transform(iterator->value));
			iterator = iterator->next;
		}
	}
}

void so_run(SceneObject* so) {
	if(so->transform.children->root == NULL) {
		so_run_one_step(so);
	}
	else {
		so_run_one_step(so);
		node_tf *iterator = so->transform.children->root;
		while(iterator != NULL) {
			so_run(so_from_transform(iterator->value));
			iterator = iterator->next;
		}
	}
}

void so_draw_one_step(SceneObject* so, Camera* cam, SunLight* light) {
	transform_refresh_matrix(&(so->transform));
	if(so->mesh != NULL && so->shader != NULL) {
		glUseProgram(so->shader->program); // On verouille le shader
		if(GLEW_VERSION_3_3) {
			glBindBuffer(GL_ARRAY_BUFFER, so->mesh->vbo);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0,(void*)( 9*so->mesh->f*sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(18*so->mesh->f*sizeof(float)));
			glEnableVertexAttribArray(2);
		}
		else {
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, so->mesh->vertices);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, so->mesh->normals);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, so->mesh->uvs);
			glEnableVertexAttribArray(2);
		}

		glUniformMatrix4fv(glGetUniformLocation(so->shader->program, "M"), 1, GL_FALSE, mat4x4_ptr(so->transform.matrix));
		glUniformMatrix4fv(glGetUniformLocation(so->shader->program, "V"), 1, GL_FALSE, mat4x4_ptr(cam->view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(so->shader->program, "P"), 1, GL_FALSE, mat4x4_ptr(cam->perspective_matrix));

		glUniform3fv(glGetUniformLocation(so->shader->program, "lightdir"), 1, light->direction);
		glUniform3fv(glGetUniformLocation(so->shader->program, "lightcolor"), 1, light->color);
		glUniform1f(glGetUniformLocation(so->shader->program, "lightforce"), light->force);
		glUniform3fv(glGetUniformLocation(so->shader->program, "camdir"), 1, camera_direction(cam));

		if(so->texture != NULL) {
			glBindTexture(GL_TEXTURE_2D, so->texture->texID);
		}

		glDrawArrays(GL_TRIANGLES, 0, so->mesh->f*3);

		glBindTexture(GL_TEXTURE_2D, 0);

		if(GLEW_VERSION_3_3) glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);


		glUseProgram(0);
	}
}

void so_draw(SceneObject* so, Camera* cam, SunLight* light) {
	if(so->transform.children->root == NULL) {
		so_draw_one_step(so, cam, light);
	}
	else {
		so_draw_one_step(so, cam, light);
		node_tf *iterator = so->transform.children->root;
		while(iterator != NULL) {
			so_draw(so_from_transform(iterator->value), cam, light);
			iterator = iterator->next;
		}
	}
}

SceneObject* so_from_transform(Transform* t){
	return (SceneObject*)t;
}

void so_add_script(SceneObject* so, Script* script) {
	list_script_put(so->scripts, script);
}

void so_rm_script(SceneObject* so, Script* script) {
	list_script_put(&scripts_to_destroy, script);
}

int so_collision_detection(SceneObject* so1, SceneObject* so2){
	if(RotRectsCollision(&(so1->transform), so1->collider, &(so2->transform), so2->collider)
	   || RotRectsCollision(&(so2->transform), so2->collider, &(so1->transform), so1->collider))
	{
		return 1;
	}
	return 0;
}

SceneObject* so_collision(SceneObject* so1, SceneObject* so2){
	if(so_collision_detection(so1, so2))
	{
		return so2;
	}
	return NULL;
}

void so_add_child(SceneObject* parent, SceneObject* child) {
	transform_add_child(&(parent->transform), &(child->transform));
}

void so_rm_child(SceneObject* parent, SceneObject* child) {
	transform_rm_child(&(parent->transform), &(child->transform));
}
