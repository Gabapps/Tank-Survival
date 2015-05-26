/*
 * Audio.c
 *
 *  Created on: 1 mai 2015
 *      Author: max
 */

#include "Audio.h"

ALshort Samples[BUFFER_SIZE];

void DisplayALError(char* text, ALenum error) {
	printf("%s%s", text, alGetString(error));
}

int audio_init()
{
	// Ouverture du device
	ALCdevice* Device = alcOpenDevice(NULL);
	if (!Device)
		return 0;

	// Création du contexte
	ALCcontext* Context = alcCreateContext(Device, NULL);
	if (!Context)
		return 0;

	// Activation du contexte
	if (!alcMakeContextCurrent(Context))
		return 0;

	return 1;
}


void sound_quit()
{
	// Récupération du contexte et du device
	ALCcontext* Context = alcGetCurrentContext();
	ALCdevice*  Device  = alcGetContextsDevice(Context);

	// Désactivation du contexte
	alcMakeContextCurrent(NULL);

	// Destruction du contexte
	alcDestroyContext(Context);

	// Fermeture du device
	alcCloseDevice(Device);
}

int sound_load(char* filename, Sound* sound)
{
	// Ouverture du fichier audio avec libsndfile
	SF_INFO FileInfos;
	SNDFILE* File = sf_open(filename, SFM_READ, &FileInfos);
	if (!File) {
		printf("Cannot open sound %s \n", filename);
		return 0;
	}

	sf_close(File);

	// Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
	sound->samplestotal = (ALsizei)(FileInfos.channels * FileInfos.frames);
	sound->samplerate = (ALsizei)(FileInfos.samplerate);

	ALenum Format;
	switch (FileInfos.channels)
	{
	case 1 :
		Format = AL_FORMAT_MONO16;
		break;
	case 2 :
		Format = AL_FORMAT_STEREO16;
		break;
	default :
		return 0;
	}
	sound->format = Format;

	sound_stream(sound);

	return 1;
}

void sound_setup_listener(vec3 pos, vec3 dir)
{
	// Définition de la position de l'écouteur (ici l'origine)
	alListener3f(AL_POSITION, pos[0], pos[1], pos[2]);

	// Définition de la vitesse de l'écouteur (ici nulle)
	alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f);

	// Définition de l'orientation de l'écouteur (ici il regarde vers l'axe des Z)
	ALfloat Orientation[] = {dir[0], dir[1], dir[2], 0.f, 1.f, 0.f};
	alListenerfv(AL_ORIENTATION, Orientation);
}

Sound* sound_add(char* filename, list_sound* sounds, float pitch, float gain)
{
	SF_INFO FileInfos;
	Sound* sound = sound_create(filename, pitch);

	alSourcePlay(sound->source);
	alGetSourcei(sound->source, AL_SOURCE_STATE, &(sound->status));

	sound->file = sf_open(filename, SFM_READ, &FileInfos);
	if (!sound->file) {
		printf("Cannot open sound %s \n", filename);
		return 0;
	}

	list_sound_put(sounds, sound);

	return sound;
}

Sound* sound_create(char* filename, float pitch)
{
	Sound* sound = malloc(sizeof(Sound));
	sound->filename = filename;
	sound->samplesread = 0;
	sound->nbbuffers = 0;

	sound->status = AL_STOPPED;

	alGenSources(1, &(sound->source));

	alSourcef(sound->source, AL_PITCH, pitch);



	//	alSource3f(source, AL_POSITION, 5.f, 0.f, 0.f);

	sound_load(filename, sound);
	alSourceQueueBuffers(sound->source, sound->nbbuffers, sound->buffers);

	return sound;
}

void sound_destroy(Sound* sound) {
	int i;
	free(sound->filename);

	for(i=0; i<NB_BUFFERS; i++) {
		if(alIsBuffer(sound->buffers[i])) {
			alDeleteBuffers(1, &(sound->buffers[i]));
		}
	}

	alDeleteSources(1, &(sound->source));

	free(sound);
}

void sound_stream(Sound* sound) {
	ALenum error;
	int i;



	//Si la lecture du son n'a pas commencé
	if(sound->samplesread == 0) {

		SF_INFO FileInfos;
		SNDFILE* File = sf_open(sound->filename, SFM_READ, &FileInfos);
		sf_seek(File, 0, SEEK_SET);
		if (!File) {
			printf("Le son %s ne peut etre ouvert\n", sound->filename);
			return ;
		}

		//Pour chaque buffer
		for(i=0; i<NB_BUFFERS; i++) {
			sf_count_t count;

			//On lit le son
			count = sf_read_short(File, Samples, BUFFER_SIZE);
			if(count == 0) {
				break;
			}
			else {
				sound->nbbuffers++;
				sound->samplesread += count;

				alGenBuffers(1, &(sound->buffers[i]));

				alBufferData(sound->buffers[i], sound->format, Samples, count * sizeof(ALushort), sound->samplerate);
				if ((error = alGetError()) != AL_NO_ERROR) {
					DisplayALError("OpenAL : ", error);
					return ;
				}

				//Si tout le son a été chargé
				if(sound->samplesread==sound->samplestotal) break;
			}
		}
		sf_close(File);
	}
	//La lecture du son est en cours
	else {
		ALint processed;
		// Get status
		alGetSourceiv(sound->source, AL_BUFFERS_PROCESSED, &processed);
		// If some buffers have been played, unqueue them
		// then load new audio into them, then add them to the queue
		if (processed > 0)
		{
			ALuint BufferID;

			sf_seek(sound->file, sound->samplesread/2, SEEK_SET);
			// Pseudo code for Streaming with Open AL
			// while (processed)
			//          Unqueue a buffer
			//          Load audio data into buffer
			//               (returned by UnQueueBuffers)
			//          if successful
			//                  Queue buffer
			//                  processed--
			//          else
			//                  buffersinqueue--
			//                  if buffersinqueue == 0
			//                          finished playing !
			while (processed)
			{
				alSourceUnqueueBuffers(sound->source, 1, &BufferID);
				if ((error = alGetError()) != AL_NO_ERROR)
				{
					DisplayALError("alSourceUnqueueBuffers 1 : ", error);
				}
				//Lecture non finie
				if (sound->samplesread != sound->samplestotal)
				{

					sf_count_t count;

					//On lit le son
					count = sf_read_short(sound->file, Samples, BUFFER_SIZE);
					if(count == 0) {
						continue;
					}
					else {
						sound->samplesread += count;


						alBufferData(BufferID, sound->format, Samples, count * sizeof(ALushort), sound->samplerate);
						if ((error = alGetError()) != AL_NO_ERROR) {
							DisplayALError("OpenAL : ", error);
							return ;
						}
						alSourceQueueBuffers(sound->source, 1, &BufferID);
						if ((error = alGetError()) != AL_NO_ERROR) {
							DisplayALError("OpenAL : ", error);
							return ;
						}
					}
					processed--;
				}
				//Lecture non finie
				else
				{
					alDeleteBuffers(1, &BufferID);

					sound->nbbuffers--;
					processed--;
					if (sound->nbbuffers == 0)
					{
						break;
					}
				}
			}
		}
	}
}

list_sound* sound_init_list()
{
	return list_sound_create();
}

void sound_remove(Sound* sound, list_sound* sounds)
{
	sf_close(sound->file);
	list_sound_delete(sounds, sound, 0);
}

void sounds_play(list_sound* sounds)
{
	node_sound *iterator = sounds->root;

	while(iterator != NULL)
	{
		alGetSourcei(iterator->value->source, AL_SOURCE_STATE, &(iterator->value->status));
		//*(iterator->value->status) == AL_PLAYING
		if(iterator->value->status == AL_PLAYING)
		{
			sound_stream(iterator->value);
		}
		else
		{
			// On enleve de la liste des sons
			sound_remove(iterator->value, sounds);
		}
		iterator = iterator->next;
	}
}
