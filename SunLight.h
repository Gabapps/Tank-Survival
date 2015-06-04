/**
 * @file SunLight.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 6 Apr 2015
 * @brief Provide informations to light a scene
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

//Create a sunlight
SunLight sunlight_create(const vec3 position, const vec3 direction, const vec3 color, float force);

//Create the default sunlight
SunLight sunlight_default();

//Configure the direction of the light
void sunlight_set_direction(SunLight* light, const vec3 direction);

#endif /* SUNLIGHT_H_ */
