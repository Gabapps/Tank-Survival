/*
 * ControlSettings.h
 *
 *  Created on: 13 mai 2015
 *      Author: Gabriel
 */

#ifndef GUI_CONTROLSETTINGS_H_
#define GUI_CONTROLSETTINGS_H_

#include "Widget.h"
#include "RelativeLayout.h"
#include "TextView.h"
#include "ImageButton.h"

typedef struct ControlSettings {
	define_widget(ControlSettings);
	int player;
	int up, down, left, right, fire;
}ControlSettings;

ControlSettings* cs_create();

#endif /* GUI_CONTROLSETTINGS_H_ */
