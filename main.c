#include <stdlib.h>
#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Time.h"
#include "Game.h"
#include "Ressources.h"

#include "Scripts/SceneScript.h"
#include "Scripts/MenuSceneScript.h"
#include "Scripts/Tank.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
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

    initOpenAL();

    game_init();

    MenuSceneScript menuscenescript;
    menuscenescript.setup = menu_script_init;
    menuscenescript.run = menu_script_run;
    Scene *menu_scene = scene_create("Menu");
    menu_scene->script = (Script*) &menuscenescript;

    SceneScript scenescript;
    scenescript.setup=sc_setup;
    scenescript.run=sc_run;
    Scene *fight_scene = scene_create("Main");
    fight_scene->script = (Script*) &scenescript;

    game_add_scene(fight_scene);
    game_add_scene(menu_scene);


    game_load_scene("Menu");
    game_resume();

    glEnable(GL_DEPTH_TEST);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    while (!glfwWindowShouldClose(window_get()))
    {
    	game_update();
    	if(Game.running) {
    		input_update();
        	time_update();
        	scene_run(Game.scene);
    	}

    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // On vide les tampons couleurs et profondeur

    	scene_draw(Game.scene);

        glfwSwapBuffers(window_get());
        glfwPollEvents();
    }
    shutdownOpenAL();
    glfwDestroyWindow(window_get());
    glfwTerminate();
    return 0;
}
