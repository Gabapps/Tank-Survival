/*
 * ControlSettings.c
 *
 *  Created on: 13 mai 2015
 *      Author: Gabriel
 */

#include "ControlSettings.h"

ControlSettings* cs_create() {
	ControlSettings* cs = (ControlSettings*)layout_rel_create();

	enum {TEXTURE_BUTTON_FOCUSED, TEXTURE_BUTTON_UNFOCUSED, FONT_ARIAL};
	enum {SHADER_GUI};

	widget_set_shader_gui(SHADER_GUI);
	textview_use_font(FONT_ARIAL);

	TextView* title = textview_create();
	TextView* movetext = textview_create();
	TextView* firetext = textview_create();
	ImageButton* up = imagebutton_create();
	ImageButton* down = imagebutton_create();
	ImageButton* left = imagebutton_create();
	ImageButton* right = imagebutton_create();
	ImageButton* fire = imagebutton_create();



	widget_add_child((Widget*)cs, (Widget*)title);
	widget_add_child((Widget*)cs, (Widget*)movetext);
	widget_add_child((Widget*)cs, (Widget*)firetext);
	widget_add_child((Widget*)cs, (Widget*)up);
	widget_add_child((Widget*)cs, (Widget*)down);
	widget_add_child((Widget*)cs, (Widget*)left);
	widget_add_child((Widget*)cs, (Widget*)right);
	widget_add_child((Widget*)cs, (Widget*)fire);
	return cs;
}
