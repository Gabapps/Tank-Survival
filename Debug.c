/*
 * Debug.c
 *
 *  Created on: 22 mars 2015
 *      Author: Gabriel
 */

#include "Debug.h"

void debug_init(){
	Debug.vec = *(list_vec_create()) ;
}

void debug_show_vec(vec3 pos, vec3 vec, float scale){
	float* tab_pos = malloc(6*sizeof(float));
	vec3 vec_copy;
	vec3_duplicate(vec_copy, vec);
	vec3_scale(vec_copy, vec_copy, scale);
	vec3_add(vec_copy, pos, vec_copy);
	tab_pos[0]=vec_copy[0];
	tab_pos[1]=vec_copy[1];
	tab_pos[2]=vec_copy[2];
	tab_pos[3]=pos[0];
	tab_pos[4]=pos[1];
	tab_pos[5]=pos[2];
}

void debug_draw() {
	node_vec* iterator = Debug.vec.root;

	while(iterator != NULL) {
		glUseProgram(Debug.shader.program); // On verouille le shader

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, iterator.value);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_LINE, 0, 6);

		glDisableVertexAttribArray(0);

		glUseProgram(0);
		list_vec_delete(Debug.vec, iterator.value, 1);
		iterator = iterator->next;
	}
}
