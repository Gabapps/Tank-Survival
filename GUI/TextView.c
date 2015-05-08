/*
 * TextView.c
 *
 *  Created on: 8 mai 2015
 *      Author: Gabriel
 */

#include "TextView.h"

Texture_ID use_font = UINT32_MAX;

TextView* textview_create() {
	TextView* tv = (TextView*)malloc(sizeof(TextView));
	widget_init((Widget*)tv, NULL, textview_draw);
	tv->text = "";
	tv->mesh = NULL;
	tv->font = NULL;
	if(use_font<UINT32_MAX) textview_set_font(tv, use_font);
	return tv;
}

void textview_draw(TextView* tv) {
	if(tv->mesh) {
		Mesh* mesh = tv->mesh;

		Shader* shader = ressources_get_shader(shader_gui);
		mat4x4 ortho;
		mat4x4_ortho(ortho, -window_get_ratio(), window_get_ratio(), -1, 1, 0, 3);

		glUseProgram(shader->program);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, mesh->vertices);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, mesh->uvs);
		glEnableVertexAttribArray(2);


		glUniformMatrix4fv(glGetUniformLocation(shader->program, "M"), 1, GL_FALSE, mat4x4_ptr(tv->matrix));
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "P"), 1, GL_FALSE, mat4x4_ptr(ortho));

		float black[] = {0,0,0};

		glUniform3fv(glGetUniformLocation(shader->program, "alphaColor"), 1, black);

		if(tv->font != NULL) {
			glBindTexture(GL_TEXTURE_2D, tv->font->texID);
		}

		glDrawArrays(GL_TRIANGLES, 0, mesh->f*3);

		glBindTexture(GL_TEXTURE_2D, 0);

		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(0);


		glUseProgram(0);
	}

}

void textview_set_font(TextView* tv, Texture_ID font) {
	tv->font = ressources_get_texture(font);
}

void textview_set_text(TextView* tv, char* text) {
	tv->text = text;
	if(tv->mesh) mesh_free(tv->mesh);
	tv->mesh = mesh_get_text_view_canvas(text);
}

void textview_use_font(Texture_ID font) {
	use_font = font;
}
