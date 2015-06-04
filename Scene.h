/**
 * @file Scene.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 1 March 2015
 * @brief A scene contain sceneObjects, a camera, lights etc.
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "Camera.h"
#include "SceneObject.h"
#include "List.h"
#include "SunLight.h"
#include "GUI/GUI.h"
#include "Audio.h"

typelist(so, SceneObject*);

/**
 * \struct Scene
 * 3D world that contains the 3D objects
 */

typedef struct Scene {
	char* name;					//Nom de la scene
	list_so* sceneObjects;	//Tableau contenant les différents objets de la scene
	Script* script;				//Pour associer des fonctions à la scene
	Camera camera;				//Camera liée à la scene
	SunLight light;
	GUI* GUI;
} Scene;


/**
 * \fn Scene* scene_create(char* name)
 * \brief Create a scene
 *
 * \param name The name of the scene
 * \return An initialized scene
 */
Scene* scene_create(char* name);

/**
 * \fn void scene_destroy(Scene* scene)
 * \brief Destroy a scene
 *
 * \param scene The scene to destroy
 */
void scene_destroy(Scene* scene);

/**
 * \fn void scene_destroy_content(Scene* scene)
 * \brief Destroy the content of a scene
 *
 * \param scene The scene to empty
 */
void scene_destroy_content(Scene* scene);

/**
 * \fn void scene_setup(Scene* scene)
 * \brief Setup all the scripts
 *
 * \param scene The scene to setup
 */
void scene_setup(Scene* scene);

/**
 * \fn void scene_run(Scene* scene)
 * \brief Run all the scripts
 *
 * \param scene The scene to run
 */
void scene_run(Scene* scene);

/**
 * \fn void scene_draw(Scene* scene)
 * \brief Draw all the sceneobjects
 *
 * \param scene The scene to draw
 */
void scene_draw(Scene* scene);


/**
 * \fn void scene_add_so(Scene* scene, SceneObject* so)
 * \brief Add a scene objects as a root to a scene
 *
 * \param scene The scene
 * \param so The sceneObject to add in the scene
 */
void scene_add_so(Scene* scene, SceneObject* so);

/**
 * \fn void scene_delete_so(Scene* scene, SceneObject* so)
 * \brief Remove and destroy a scene objects from a scene
 *
 * \param scene The scene
 * \param so The sceneObject to delete of the scene
 */
void scene_delete_so(Scene* scene, SceneObject* so);

/**
 * \fn void scene_attach_so(Scene* scene, SceneObject* child, SceneObject* parent)
 * \brief Attach a root scene object to another scene object
 *
 * \param scene The scene
 * \param child The sceneObject to be attach to the parent
 * \param parent The parent sceneObject
 */
void scene_attach_so(Scene* scene, SceneObject* child, SceneObject* parent);

/**
 * \fn void scene_detach_so(Scene* scene, SceneObject* so)
 * \brief Detach a scene object from his parents and change it as a root
 *
 * \param scene The scene
 * \param so The sceneObject to detach to his parent
 */
void scene_detach_so(Scene* scene, SceneObject* so);

#endif /* SCENE_H_ */
