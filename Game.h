/**
 * @file Game.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 1 Mar 2015
 * @brief The global Game structure centralizes the scenes and provides functions to switch between them.
 */

#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "List.h"
#include "Time.h"
#include "Window.h"
#include "Audio.h"

typelist(scene, Scene*);

/*!
 * \struct Game_s
 * Structure that contains all the scenes of the game
 */
typedef struct Game_s{
	char* name;
	Scene* scene;
	Scene* scene_to_load;
	list_scene* scenes;
	int running;
}Game_s;

Game_s Game;

/**
 * \fn void game_init()
 * \brief Launch the game
 */
void game_init();

/**
 * \fn void game_load_scene(char* name)
 * \brief Load a scene by name
 *
 * \param name The name of the scene to be load
 *
 */
void game_load_scene(char* name);

/**
 * \fn void game_reload_current_scene()
 * \brief Reload the current scene
 */
void game_reload_current_scene();

/**
 * \fn void game_add_scene(Scene *scene)
 * \brief Add a scene to the game
 *
 * \param scene The scene to add
 *
 */
void game_add_scene(Scene *scene);

/**
 * \fn void game_pause()
 * \brief Pause the game
 */
void game_pause();

/**
 * \fn void game_resume()
 * \brief Resume the game
 */
void game_resume();

/**
 * \fn void game_update()
 * \brief Update the game
 */
void game_update();

/**
 * \fn void game_exit()
 * \brief Exit the game
 */
void game_exit();

#endif /* GAME_H_ */
