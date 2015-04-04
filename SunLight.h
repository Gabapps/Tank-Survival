/*
 * SunLight.h
 *
 *  Created on: 2 avr. 2015
 *      Author: Gabriel
 */

#ifndef SUNLIGHT_H_
#define SUNLIGHT_H_

#include "Math.h"

typedef struct SunLight {
	vec3 position;
	vec3 direction;
	vec3 color;
	float force;
} SunLight;

SunLight sunlight_create(const vec3 position, const vec3 direction, const vec3 color, float force);

SunLight sunlight_default();

void sunlight_set_direction(SunLight* light, const vec3 direction);

#endif /* SUNLIGHT_H_ */