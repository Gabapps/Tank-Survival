/*
 * Game.c

 *
 *  Created on: 17 avr. 2015
 *      Author: Gabriel
 */
#include "Game.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    game_exit();
}

void game_load_scene_direct(Scene* scene);

void game_init() {
	window_open();
	glfwSetErrorCallback(error_callback);
	glfwMakeContextCurrent(window_get());
	glfwSetKeyCallback(window_get(), key_callback);

	glewExperimental=GL_FALSE;
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		printf("OpenGL Error: %d\n", error);
	}
	GLenum glewinit = glewInit();
	if (glewinit != GLEW_OK) {
		printf("Glew's not okay! %s\n", glewGetErrorString(glewinit));
		exit(EXIT_FAILURE);
	}
	if(!GLEW_VERSION_3_3) {
		printf("Your graphic card doesn't support OpenGL 3.3 !\nSwitching in OpenGL 2.1 compatibility mode\n");
	}
	if (!GLEW_VERSION_2_1) {  // check that the machine supports the 2.1 API.
		printf("Your graphic card doesn't support OpenGL 2.1 !\nCheck if your video drivers are up to date.\n");
		exit(EXIT_FAILURE);
	}

	sounds = sound_create_playlist();

	Game.running = 0;
	Game.scene = NULL;
	Game.scene_to_load = NULL;
	Game.scenes = list_scene_create();
	audio_init();
}

void game_pause() {
	Game.running = 0;
}

void game_resume() {
	Game.running = 1;
}

void game_update() {
	if(Game.scene_to_load) {
		game_load_scene_direct(Game.scene_to_load);
		Game.scene_to_load = NULL;
	}
}

void game_load_scene_direct(Scene* scene) {
	if(Game.scene) scene_destroy_content(Game.scene);
	Game.scene = scene;
	time_init();
	scene_setup(scene);
}

void game_load_scene(char* name) {
	node_scene* iterator = Game.scenes->root;

	while(iterator != NULL) {
		if(strcmp(name, iterator->value->name) == 0) {
			Game.scene_to_load = iterator->value;
			break;
		}
		iterator = iterator->next;
	}
}

void game_reload_current_scene() {
	Game.scene_to_load = Game.scene;
}

void game_add_scene(Scene *scene) {
	list_scene_put(Game.scenes, scene);
}

void game_exit() {
	audio_quit();
	window_close();
}
