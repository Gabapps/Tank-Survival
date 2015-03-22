/*
 * Debug.c
 *
 *  Created on: 22 mars 2015
 *      Author: Gabriel
 */

#include "Debug.h"

debug_init(){
	Debug.vec = *(list_vec_create()) ;
}

debug_show_vec(vec3 pos, vec3 vec, float scale){
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
