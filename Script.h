/*
 * Script.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef SCRIPT_H_
#define SCRIPT_H_

#include "Scene.h"
#include "SceneObject.h"

typedef void (*fct_script) (struct Script*, SceneObject*, Scene*);

typedef struct Script {
	char* name;
	fct_script setup;
	fct_script run;;
} Script;

Script* script_create(char*, setup, run);
void script_destroy(Script*);

#endif /* SCRIPT_H_ */
