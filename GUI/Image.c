/*
 * Image.c
 *
 *  Created on: 20 avr. 2015
 *      Author: Gabriel
 */

#include "Image.h"

Texture_ID use_texture = UINT32_MAX;

Image* image_create() {
	Image* img = (Image*)malloc(sizeof(Image));
	widget_init((Widget*)img, image_run, image_draw);
	img->image = NULL;
	vec3_create(img->alphaColor, -1, 0, 0);
	if(use_texture<UINT32_MAX) image_set_texture(img, use_texture);
	return img;
}

void image_run(Image *image) {

}

void image_draw(Image *image) {
	Mesh* mesh = mesh_get_canvas();
	//Shader* shader = ressources_get_shader(SHADER_GUI);
	Shader* shader = ressources_get_shader(shader_gui);
	mat4x4 ortho;
	mat4x4_ortho(ortho, -window_get_ratio(), window_get_ratio(), -1, 1, 0, 3);

	glUseProgram(shader->program);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, mesh->vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, mesh->uvs);
	glEnableVertexAttribArray(2);


	glUniformMatrix4fv(glGetUniformLocation(shader->program, "M"), 1, GL_FALSE, mat4x4_ptr(image->matrix));
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "P"), 1, GL_FALSE, mat4x4_ptr(ortho));

	glUniform3fv(glGetUniformLocation(shader->program, "alphaColor"), 1, image->alphaColor);

	if(image->image != NULL) {
		glBindTexture(GL_TEXTURE_2D, image->image->texID);
	}

	glDrawArrays(GL_TRIANGLES, 0, mesh->f*3);

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(0);


	glUseProgram(0);

}

void image_set_texture(Image *image, Texture_ID id) {
	image->image = ressources_get_texture(id);
	widget_resize((Widget*)image, (float)image->image->width, (float)image->image->height);
	widget_resize((Widget*)image, 1,0);
	widget_refresh_matrix((Widget*)image);
}

void image_set_alphaColor(Image *image, float r, float g, float b) {
	vec3_create(image->alphaColor, r, g, b);
}

void image_use_texture(Texture_ID id) {
	use_texture = id;
}
