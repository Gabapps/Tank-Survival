/*
 * Script.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef SCRIPT_H_
#define SCRIPT_H_

#define define_script(type) char* name; void (*setup) (struct type*, SceneObject*); void (*run) (struct type*, SceneObject*);
#define setup_script(type) void (*setup) (struct type*, SceneObject*)
#define run_script(type) void (*run) (struct type*, SceneObject*)

typedef struct Script Script;
typedef struct SceneObject SceneObject;
typedef void (*fct_script) (Script*, SceneObject*);

struct Script {
	define_script(Script);
};

/**
 * \fn Script* script_create(char* name, fct_script setup_fct, fct_script run_fct)
 * \brief Instanciate a new script.
 *
 * \param name Name of the new script.
 * \param setup_fct The setup function of the script.
 * \param run_fct The run function of the script.
 * \return The new instantiated script.
 */
Script* script_create(char* name, setup_script(Script), run_script(Script));

/* \fn void script_destroy(Script* script)
 * \brief Destroy a script.
 *
 * \param script Script to destroy.
 */
void script_destroy(Script* script);

#endif /* SCRIPT_H_ */
