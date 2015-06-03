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

/*!
 * \struct Audio
 * Audio structure
 */
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

/**
 * \fn int audio_init()
 * \brief Initialize OpenAL
 * \return 0 if something went wrong, otherwise
 */
int audio_init();


/**
 * \fn int audio_quit()
 * \brief Exit OpenAL
 */
void audio_quit();


/**
 * \fn int sound_load(char* filename, Sound* sound)
 * \brief Load the configuration and the beginning of a sound
 *
 * \param[out] sound The sound
 * \param[in] filename The path to the file
 *
 * \return 0 if something went wrong, otherwise
 */
int sound_load(char* filename, Sound* sound);


/**
 * \fn Sound* sound_add(char* filename,list_sound* sounds, float pitch, float gain)
 * \brief Add a sound to a sound list
 *
 * \param[out] sounds The sound list
 * \param[in] filename The path to the file
 * \param[in] pitch Multiply the pitch of the sound by this factor
 * \param[in] gain Multiply the gain of the sound by this factor
 *
 * \return The sound created
 */
Sound* sound_add(char* filename,list_sound* sounds, float pitch, float gain);


/**
 * \fn Sound* sound_create(char* filename, float pitch, float gain)
 * \brief Allocate and load a sound
 *
 * \param[in] filename The path to the file
 * \param[in] pitch Multiply the pitch of the sound by this factor
 * \param[in] gain Multiply the gain of the sound by this factor
 *
 * \return The sound created
 */
Sound* sound_create(char* filename, float pitch, float gain);


/**
 * \fn void sound_stream(Sound* sound)
 * \brief Update the buffers of a sound
 *
 * \param[in, out] sound The sound
 */
void sound_stream(Sound* sound);


/**
 * \fn void sound_remove(Sound* sound, list_sound* sounds)
 * \brief Remove a sound from a sound list
 *
 * \param[in] sound The sound
 * \param[out] sounds The list of sounds
 */
void sound_remove(Sound* sound, list_sound* sounds);


/**
 * \fn void sound_remove(Sound* sound, list_sound* sounds)
 * \brief void sound_setup_listener(vec3 pos, vec3 dir)
 *
 * \param[in] pos The position of the listener
 * \param[in] dir The direction of the listener
 */
void sound_setup_listener(vec3 pos, vec3 dir);


/**
 * \fn void sound_destroy(Sound* sound)
 * \brief Destroy a sound
 *
 * \param[out] sound The sound to be detroyed
 */
void sound_destroy(Sound* sound);


/**
 * \fn list_sound* sound_create_playlist()
 * \brief Return an initialized a list of sounds
 *
 * \return The list of sounds created
 */
list_sound* sound_create_playlist();


/**
 * \fn void sounds_play(list_sound* sounds)
 * \brief Play a list of sounds
 *
 * \param[in, out] sounds The list of sounds
 */
void sounds_play(list_sound* sounds);


#endif /* AUDIO_H_ */
