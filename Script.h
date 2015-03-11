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

/**
 * \fn Script* script_create(char* name, fct_script setup_fct, fct_script run_fct)
 * \brief Instanciate a new script.
 *
 * \param name Name of the new script.
 * \param setup_fct The setup function of the script.
 * \param run_fct The run function of the script.
 * \return The new instantiated script.
 */
Script* script_create(char* name, fct_script setup_fct, fct_script run_fct);

/* \fn void script_destroy(Script* script)
 * \brief Destroy a script.
 *
 * \param script Script to destroy.
 */
void script_destroy(Script* script);

#endif /* SCRIPT_H_ */
