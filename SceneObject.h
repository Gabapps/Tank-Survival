/*
 * SceneObject.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

typedef struct SceneObject {
	Transform transform;
	char* name;
	Mesh* mesh;
	Shader* shader;
	Script* scripts;
	int count_script;
} SceneObject;

/**
 * \fn SceneObject* so_create(char* name, Transform t)
 * \brief Instanciate a new sceneObject.
 *
 * \param name Name of the new sceneObject.
 * \param t Transform of the new sceneObject.
 * \return The new instantiated sceneObject.
 */
SceneObject* so_create(char* name, Transform t);

/**
 * \fn so_detroy(SceneObject* so)
 * \brief Destroy a SceneObject.
 *
 * \param so SceneObject to destroy.
 * \return The new instantiated sceneObject.
 */
void so_detroy(SceneObject* so);

/**
 * \fn SceneObject* so_duplicate(SceneObject* so, char* name, Transform t)
 * \brief Instanciate a new sceneObject.
 *
 * \param so The SceneObject to duplicate.
 * \param name Name of the new sceneObject.
 * \param t Transform of the new sceneObject.
 * \return The new instantiated sceneObject.
 */
SceneObject* so_duplicate(SceneObject* so, char* name, Transform t);

/**
 * \fn so_init(SceneObject* so, Scene* sc)
 * \brief Initiate all the script of a sceneObject.
 *
 * \param so The sceneObject to initiate.
 * \param sc The current Scene
 */
void so_init(SceneObject* so, Scene* sc);

/**
 * \fn so_run(SceneObject* so, Scene* sc)
 * \brief Run all the script of a sceneObject.
 *
 * \param so The sceneObject to run.
 * \param sc The current Scene
 */
void so_run(SceneObject* so, Scene* sc);

/**
 * \fn so_draw(SceneObject* so, Camera* cam)
 * \brief Render a sceneObject in the current scene.
 *
 * \param so The SceneObject to initiate.
 * \param sc The current Scene
 */
void so_draw(SceneObject* so, Scene* sc);

#endif /* SCENEOBJECT_H_ */
