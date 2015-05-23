/*
 * Audio.h
 *
 *  Created on: 1 mai 2015
 *      Author: max
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <al.h>
#include <alc.h>
#include <sndfile.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "Math.h"

typedef struct Sound{
	ALuint source;
	ALuint buffer;
	ALint status;
} Sound;

typelist(sound, Sound*);

int initOpenAL();
void shutdownOpenAL();
ALuint loadSound(char* filename);
Sound* addSound(char* filename,list_sound* sounds, float pitch);
Sound* createSound(char* filename, float pitch);
void removeSound(Sound* sound, list_sound* sounds);
void setupListener(float x, float y, float z, float u, float v, float w);
list_sound* initSoundList();

void playSounds(list_sound* sounds);


#endif /* AUDIO_H_ */
