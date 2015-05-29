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

int main(void)
{

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
    //sound_setup_listener(fight_scene->camera.pos, fight_scene->camera.pos);

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

    glfwDestroyWindow(window_get());
    glfwTerminate();
    return 0;
}
