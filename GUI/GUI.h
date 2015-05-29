/*
 * GUI.h
 *
 *  Created on: 4 avr. 2015
 *      Author: Gabriel
 */

#ifndef GUI_H_
#define GUI_H_

/* A GUI (Graphic User Interface) is a 2D interface included is the 3D world.
 * It is used here to render the main menu with widgets like buttons or images.
 *
 * A GUI works with several GUI pages that can be select easily.
 *
 * You can make a GUI page by making a GUI page structure.
 * Here's an example :
 *
 * If you want to make this hierarchy :
 *
 * RelativeLayout mainlayout
 * ---RelativeLayout rightlayout
 * ------ImageButton imgbt
 * ---RelativeLayout leftlayout
 * ------Image img
 * ------Textview tv
 *
 * Make this structure :
 *
 * typedef struct MenuGUI {
 *    parse_widget(RelativeLayout, mainlayout);
 *
 *       parse_widget(RelativeLayout, rightlayout);
 *
 *          parse_widget(ImageButton, imgbt);
 *
 *       parse_widget(RelativeLayout, leftlayout);
 *
 *          parse_widget(Image, img);
 *
 *          parse_widget(Textview, tv);
 * } MenuGUI;
 *
 * MenuGUI Menu;
 *
 * Then is the scene script do :
 *
 * GUI_prepare_parse(&Menu, sizeof(MenuGUI));
 *
 * parse_config(Menu, mainlayout, 2); //because he has two children
 * parse_config(Menu, rightlayout, 1);
 * parse_config(Menu, leftlayout, 2);
 *
 * and then :
 *
 * GUI_parse(Menu.mainlayout, &Menu);
 *
 * GUI_add_root(GUI, &Menu);
 */

#include "Widget.h"
#include <stddef.h>

#define parse_widget(type, name) type* name; unsigned int nb_##name

#define parse_config(structname, nameparam, nbchild)\
	structname.nb_##nameparam = nbchild

typedef struct GUI {
	list_widget* roots;
	Widget* current_root;
} GUI;

//Initialize GUI
void GUI_init();

//Create a GUI
GUI* GUI_create();

//Draw a GUI
void GUI_draw(GUI* gui);

//Run a GUI
void GUI_run(GUI* gui);

//Destroy a GUI
void GUI_destroy(GUI* gui);

//Add a new GUI page to a GUI
void GUI_add_root(GUI* gui, Widget* root);

//Select a GUI page
void GUI_select_root(GUI* gui, unsigned int index);

//Prepare a GUI page structure to by parsed
void GUI_prepare_parse(void* parsing_structure, size_t size);

//Parse a GUI page structure and auto-add child to parent
void GUI_parse(Widget* root, void* parsing_structure);

#endif /* GUI_H_ */
