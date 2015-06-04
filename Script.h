/**
 * @file Script.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 1 March 2015
 * @brief A script is a gameplay code assigned to a scene object or a scene.
 * To use of script, you need to assigned two functions :
 * - setup : This function is executed when initializing a scene or a scene object.
 * - run : This function is executed each frame.
 */

#ifndef SCRIPT_H_
#define SCRIPT_H_

#define define_script(type)\
	char* name;\
	void (*setup) (struct type*, SceneObject*);\
	void (*run) (struct type*, SceneObject*);
#define setup_script(type) void (*setup) (struct type*, SceneObject*)
#define run_script(type) void (*run) (struct type*, SceneObject*)

typedef struct Script Script;
typedef struct SceneObject SceneObject;
typedef void (*fct_script) (Script*, SceneObject*);

/**
 * \struct Script
 * \brief
 * A script is a gameplay code assigned to a scene object or a scene.
 * To use of script, you need to assigned two functions :
 * - setup : This function is executed when initializing a scene or a scene object.
 * - run : This function is executed each frame.
 */
struct Script {
	define_script(Script);
};

#endif /* SCRIPT_H_ */
