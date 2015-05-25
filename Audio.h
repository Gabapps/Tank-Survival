/*
 * Audio.h
 *
 *  Created on: 1 mai 2015
 *      Author: max
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <sndfile.h>
#include <al.h>
#include <alc.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "Math.h"

#define NB_BUFFERS 4
#define BUFFER_SIZE 4096*20

typedef struct Sound{
	char* filename;
	ALenum format;
	ALsizei samplerate;
	ALsizei samplesread;
	ALsizei samplestotal;
	ALuint source;
	ALuint buffers[NB_BUFFERS];
	ALuint nbbuffers;
	ALint status;
} Sound;

typelist(sound, Sound*);

int sound_init();
void sound_quit();
int sound_load(char* filename, Sound* sound);
Sound* sound_add(char* filename,list_sound* sounds, float pitch, float gain);
Sound* sound_create(char* filename, float pitch);
void sound_stream(Sound* sound);
void sound_remove(Sound* sound, list_sound* sounds);
void sound_setup_listener(vec3 pos, vec3 dir);
list_sound* sound_init_list();

void sounds_play(list_sound* sounds);


#endif /* AUDIO_H_ */
