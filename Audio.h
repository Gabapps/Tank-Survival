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

#define NB_BUFFERS 8
#define BUFFER_SIZE 4096

typedef struct Sound{
	char* filename;
	SNDFILE* file;
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
list_sound* sounds;

//Initialize OpenAL
int audio_init();

//Exit OpenAL
void audio_quit();

//Load the configuration and the beginning of a sound
int sound_load(char* filename, Sound* sound);

//Add a sound to a playlist
Sound* sound_add(char* filename,list_sound* sounds, float pitch, float gain);

//Allocate and load a sound
Sound* sound_create(char* filename, float pitch, float gain);

//Update the buffers of a sound
void sound_stream(Sound* sound);

//Remove a sound from a playlist
void sound_remove(Sound* sound, list_sound* sounds);

//Configure the 3D coordinates of the listener
void sound_setup_listener(vec3 pos, vec3 dir);

//Destroy a sound
void sound_destroy(Sound* sound);

//Return an initialized sound playlist
list_sound* sound_create_playlist();

//Play a playlist
void sounds_play(list_sound* sounds);


#endif /* AUDIO_H_ */
