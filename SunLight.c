/*
 * SunLight.c
 *
 *  Created on: 4 avr. 2015
 *      Author: Gabriel
 */

#include "SunLight.h"

SunLight sunlight_create(const vec3 position, const vec3 direction, const vec3 color) {
	SunLight light;
	vec3_cpy(light.position, position);
	vec3_cpy(light.direction, direction);
	vec3_cpy(light.color, color);
	return light;
}

SunLight sunlight_default() {
	//SunLight light = {{0,0,0}, {0,-1,0}, {1,1,1} };
	SunLight light = {{0,0,0}, {-1,-1,-1}, {1,1,1} };
	return light;
}
