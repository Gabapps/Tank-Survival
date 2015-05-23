/*
 * MenuSceneScript.h
 *
 *  Created on: 3 mai 2015
 *      Author: Gabriel
 */

#ifndef SCRIPTS_MENUSCENESCRIPT_H_
#define SCRIPTS_MENUSCENESCRIPT_H_

#include "../Script.h"

#include "../GUI/GUI.h"
#include "../GUI/ImageButton.h"
#include "../GUI/RelativeLayout.h"
#include "../GUI/Button.h"
#include "../GUI/TextView.h"

typedef struct MenuSceneScript {
	define_script(MenuSceneScript);
} MenuSceneScript;

typedef struct MenuGUI {
	parse_widget(RelativeLayout, main_layout);

	parse_widget(ImageButton, play);

	parse_widget(ImageButton, settings);

	parse_widget(ImageButton, quit);

	parse_widget(Image, background);

} MenuGUI;

typedef struct SettingsGUI {
	parse_widget(RelativeLayout, main_layout);

	parse_widget(TextView, title);

	parse_widget(ImageButton, play);

	parse_widget(ImageButton, settings);

	parse_widget(ImageButton, cancel);

	parse_widget(ImageButton, savequit);

} SettingsGUI;

MenuGUI menuGUI;
SettingsGUI settingsGUI;

void menu_script_init(MenuSceneScript* script, SceneObject* so);
void menu_script_run(MenuSceneScript* script, SceneObject* so);
void menu_script_load_views();

void menu_script_init(MenuSceneScript* script, SceneObject* so) {
	ressources_init();
	ressources_load();

	init_controlsTable();

	controls_create("Up", GLFW_KEY_UP);
	controls_create("Down", GLFW_KEY_DOWN);
	controls_create("Left", GLFW_KEY_LEFT);
	controls_create("Right", GLFW_KEY_RIGHT);
	controls_create("Enter", GLFW_KEY_ENTER);

	GUI_init();
	GUI* menu = GUI_create();

	menu_script_load_views();

	GUI_parse((Widget*)menuGUI.main_layout, &menuGUI);

	GUI_add_root(menu, (Widget*)menuGUI.main_layout);

	Game.scene->GUI = menu;
}

void menu_script_load_views() {
	enum {TEXTURE_BACKGROUND, TEXTURE_BUTTON_FOCUSED_PLAY, TEXTURE_BUTTON_UNFOCUSED_PLAY,TEXTURE_BUTTON_FOCUSED_SETTINGS,TEXTURE_BUTTON_UNFOCUSED_SETTINGS, TEXTURE_BUTTON_FOCUSED_QUIT,TEXTURE_BUTTON_UNFOCUSED_QUIT};
	enum {SHADER_GUI};

	widget_set_shader_gui(SHADER_GUI);

	parse_config(menuGUI, main_layout, 4);
	parse_config(menuGUI, background, 0);
	parse_config(menuGUI, play, 0);
	parse_config(menuGUI, settings, 0);
	parse_config(menuGUI, quit, 0);

	menuGUI.main_layout = layout_rel_create();
	image_use_texture(TEXTURE_BUTTON_UNFOCUSED_PLAY);
	menuGUI.play = imagebutton_create();
	image_use_texture(TEXTURE_BUTTON_UNFOCUSED_SETTINGS);
	menuGUI.settings = imagebutton_create();
	image_use_texture(TEXTURE_BUTTON_UNFOCUSED_QUIT);
	menuGUI.quit = imagebutton_create();
	menuGUI.background = image_create();

	image_set_texture(menuGUI.background, TEXTURE_BACKGROUND);

	widget_set_position((Widget*)menuGUI.play, 0, 0.5);
	widget_set_position((Widget*)menuGUI.settings, 0, 0);
	widget_set_position((Widget*)menuGUI.quit, 0, -0.5);
	widget_set_position((Widget*)menuGUI.background, 0, 0);
	widget_resize((Widget*)menuGUI.background, RESIZE_LINEAR, 2);

	//	textview_set_text(menuGUI.title, "Tank survival");

	void onFocusPlay(Button *widget, int focus) {
		if(focus) image_set_texture((Image*)widget->parent, TEXTURE_BUTTON_FOCUSED_PLAY);
		else image_set_texture((Image*)widget->parent, TEXTURE_BUTTON_UNFOCUSED_PLAY);
	}

	void onFocusSettings(Button *widget, int focus) {
		if(focus) image_set_texture((Image*)widget->parent, TEXTURE_BUTTON_FOCUSED_SETTINGS);
		else image_set_texture((Image*)widget->parent, TEXTURE_BUTTON_UNFOCUSED_SETTINGS);
	}

	void onFocusQuit(Button *widget, int focus) {
		if(focus) image_set_texture((Image*)widget->parent, TEXTURE_BUTTON_FOCUSED_QUIT);
		else image_set_texture((Image*)widget->parent, TEXTURE_BUTTON_UNFOCUSED_QUIT);
	}

	Button* playbutton = imagebutton_get_button(menuGUI.play);
	Button* settingsbutton = imagebutton_get_button(menuGUI.settings);
	Button* quitbutton = imagebutton_get_button(menuGUI.quit);

	//PLAY
	void onClickPlay(Button *widget) {
		game_load_scene("Main");
	}
	button_set_onFocusListener(playbutton, onFocusPlay);
	button_set_onClickListener(playbutton, onClickPlay);
	button_set_near_buttons(playbutton, NULL, NULL, NULL, settingsbutton);
	//SETTINGS
	void onClickSettings(Button *widget) {

	}
	button_set_onFocusListener(settingsbutton, onFocusSettings);
	button_set_onClickListener(settingsbutton, onClickSettings);
	button_set_near_buttons(settingsbutton, NULL, NULL, playbutton, quitbutton);
	//QUIT
	void onClickQuit(Button *widget) {
		game_exit();
	}
	button_set_onFocusListener(quitbutton, onFocusQuit);
	button_set_onClickListener(quitbutton, onClickQuit);
	button_set_near_buttons(quitbutton, NULL, NULL, settingsbutton,  NULL);


	button_focus(playbutton);
}


void menu_script_run(MenuSceneScript* script, SceneObject* so) {

}

#endif /* SCRIPTS_MENUSCENESCRIPT_H_ */
