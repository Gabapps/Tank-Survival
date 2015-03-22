/*
 * Debug.h
 *
 *  Created on: 22 mars 2015
 *      Author: Gabriel
 */

#ifndef DEBUG_H_
#define DEBUG_H_

typedef struct Debug_s {

} Debug_s;

Debug_s Debug;

debug_init();

debug_show_vec(vec3 pos, vec3 vec, float scale);

debug_draw();

#endif /* DEBUG_H_ */
