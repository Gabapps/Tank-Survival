/*
 * Game.c

 *
 *  Created on: 17 avr. 2015
 *      Author: Gabriel
 */
#include "Game.h"

void game_pause() {
	Game.running = 0;
}

void game_resume() {
	Game.running = 1;
}
