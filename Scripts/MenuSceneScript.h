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

	parse_widget(TextView, title);

	parse_widget(ImageButton, play);

	parse_widget(ImageButton, settings);

	parse_widget(ImageButton, quit);

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
	enum {TEXTURE_BUTTON_FOCUSED, TEXTURE_BUTTON_UNFOCUSED, FONT_ARIAL};
	enum {SHADER_GUI};

	widget_set_shader_gui(SHADER_GUI);
	textview_use_font(FONT_ARIAL);

	parse_config(menuGUI, main_layout, 4);
	parse_config(menuGUI, title, 0);
	parse_config(menuGUI, play, 0);
	parse_config(menuGUI, settings, 0);
	parse_config(menuGUI, quit, 0);

	image_use_texture(TEXTURE_BUTTON_UNFOCUSED);

	menuGUI.main_layout = layout_rel_create();
	menuGUI.title = textview_create();
	menuGUI.play = imagebutton_create();
	menuGUI.settings = imagebutton_create();
	menuGUI.quit = imagebutton_create();

	widget_set_position((Widget*)menuGUI.title, 0, 0.8);
	widget_set_position((Widget*)menuGUI.play, 0, 0.5);
	widget_set_position((Widget*)menuGUI.settings, 0, 0);
	widget_set_position((Widget*)menuGUI.quit, 0, -0.5);

	textview_set_text(menuGUI.title, "Tank survival");

	void onFocus(Button *widget, int focus) {
		if(focus) image_set_texture((Image*)widget->parent, TEXTURE_BUTTON_FOCUSED);
		else image_set_texture((Image*)widget->parent, TEXTURE_BUTTON_UNFOCUSED);
	}

	Button* playbutton = imagebutton_get_button(menuGUI.play);
	Button* settingsbutton = imagebutton_get_button(menuGUI.settings);
	Button* quitbutton = imagebutton_get_button(menuGUI.quit);

	//PLAY
	void onClickPlay(Button *widget) {
		game_load_scene("Main");
	}
	button_set_onFocusListener(playbutton, onFocus);
	button_set_onClickListener(playbutton, onClickPlay);
	button_set_near_buttons(playbutton, NULL, NULL, NULL, settingsbutton);
	imagebutton_set_text(menuGUI.play, "Play");
	//SETTINGS
	void onClickSettings(Button *widget) {

	}
	button_set_onFocusListener(settingsbutton, onFocus);
	button_set_onClickListener(settingsbutton, onClickSettings);
	button_set_near_buttons(settingsbutton, NULL, NULL, playbutton, quitbutton);
	imagebutton_set_text(menuGUI.settings, "Settings");
	//QUIT
	void onClickQuit(Button *widget) {
		game_exit();
	}
	button_set_onFocusListener(quitbutton, onFocus);
	button_set_onClickListener(quitbutton, onClickQuit);
	button_set_near_buttons(quitbutton, NULL, NULL, settingsbutton,  NULL);
	imagebutton_set_text(menuGUI.quit, "Quit");


	button_focus(playbutton);
}


void menu_script_run(MenuSceneScript* script, SceneObject* so) {

}

#endif /* SCRIPTS_MENUSCENESCRIPT_H_ */
