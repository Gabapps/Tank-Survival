/*
 * Debug.h
 *
 *  Created on: 22 mars 2015
 *      Author: Gabriel
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "Shader.h"
#include "Math.h"
#include "List.h"

typelist(vec, float*);

typedef struct Debug_s {
	list_vec vec;
	Shader shader;
} Debug_s;

Debug_s Debug;

void debug_init();

void debug_show_vec(vec3 pos, vec3 vec, float scale);

void debug_draw();

#endif /* DEBUG_H_ */
