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
#include "Texture.h"
#include "SunLight.h"
#include "Physics.h"
#include "Time.h"

typelist(script, Script*);

typedef struct SceneObject {
	Transform transform;
	char* name;
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
	list_script* scripts;
	BoxCollider* collider;
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
void so_destroy(SceneObject* so);

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
 * \param light The current scene's light.
 */
void so_draw(SceneObject* so, Camera* cam, SunLight* light);

/**
 * \fn SceneObject* so_from_transform(Transform*)
 *
 * \brief get a sceneObject associated to a transform.
 * \param t The transform of a sceneObject.
 * \return The sceneObject associated.
 *
 */
SceneObject* so_from_transform(Transform* t);

void so_add_script(SceneObject* so, Script* script);

void so_rm_script(SceneObject* so, Script* script);

/**
 * \fn int so_collision_detection(SceneObject* so1, SceneObject* so2)
 *
 * \brief Detect collisions between two SceneObjects.
 * \param so1 The first SceneObject.
 * \param so2 The second SceneObject.
 *
 * \return 1 if there is a collision. 0 otherwise.
 *
 */
int so_collision_detection(SceneObject* so1, SceneObject* so2);

/**
 * \fn SceneObject* so_collision(SceneObject* so1, SceneObject* so2);
 *
 * \brief Detect collisions between two SceneObjects.
 * \param so1 The first SceneObject.
 * \param so2 The second SceneObject.
 *
 * \return The second SceneObject (so2).
 *
 */
SceneObject* so_collision(SceneObject* so1, SceneObject* so2);

void so_add_child(SceneObject* parent, SceneObject* child);

void so_rm_child(SceneObject* parent, SceneObject* child);

#endif /* SCENEOBJECT_H_ */
