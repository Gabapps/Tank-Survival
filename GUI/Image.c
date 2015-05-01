/*
 * Image.c
 *
 *  Created on: 20 avr. 2015
 *      Author: Gabriel
 */

#include "Image.h"

Image* image_create() {
	Image* img = (Image*)malloc(sizeof(Image));
	widget_init((Widget*)img, image_setup, image_draw);
	img->image = NULL;
	return img;
}

void image_setup(Image *image) {
	image_set_texture(image, TEXTURE_GROUND);
}

void image_draw(Image *image) {
	Mesh* mesh = mesh_get_canvas();
	Shader* shader = ressources_get_shader(SHADER_GUI);
	mat4x4 ortho;
	mat4x4_ortho(ortho, -window_get_ratio(), window_get_ratio(), -1, 1, 0, 3);

	glUseProgram(shader->program);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, mesh->vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, mesh->uvs);
	glEnableVertexAttribArray(2);


	glUniformMatrix4fv(glGetUniformLocation(shader->program, "M"), 1, GL_FALSE, mat4x4_ptr(image->matrix));
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "P"), 1, GL_FALSE, mat4x4_ptr(ortho));

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
