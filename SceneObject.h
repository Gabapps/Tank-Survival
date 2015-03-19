/*
 * SceneObject.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include <stdlib.h>

#include "Shader.h"
#include "Script.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "List.h"

typelist(script, Script*);

typedef struct SceneObject {
	Transform transform;
	char* name;
	Mesh* mesh;
	Shader* shader;
	list_script* scripts;
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
 * \fn so_setup(SceneObject* so)
 * \brief Initiate all the script of a sceneObject.
 *
 * \param so The sceneObject to initiate.
 */
void so_setup(SceneObject* so);

/**
 * \fn so_run(SceneObject* so)
 * \brief Run all the script of a sceneObject.
 *
 * \param so The sceneObject to run.
 */
void so_run(SceneObject* so);

/**
 * \fn so_draw(SceneObject* so, Camera* cam)
 * \brief Render a sceneObject in the current scene.
 *
 * \param so The SceneObject to initiate.
 * \param cam The current scene's camera.
 */
void so_draw(SceneObject* so, Camera* cam);

/**
 * \fn SceneObject* so_from_transform(Transform*);
 *
 * \brief get a sceneObject associated to a transform.
 * \param t The transform of a sceneObject.
 * \return The sceneObject associated.
 *
 */
SceneObject* so_from_transform(Transform* t);


void so_add_script(SceneObject* so, Script* script);

#endif /* SCENEOBJECT_H_ */
