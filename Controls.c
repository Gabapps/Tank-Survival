/*
 * Controls.c
 *
 * Created on: 9 mars 2015
 * Author: max
 */

#include "Controls.h"


Controls* controlsTable[30];

void init_controlsTable()
{
	numberOfControls = 0;
	int i;
	for(i=0; i<20; ++i)
	{
		controlsTable[i] = (Controls*) malloc(sizeof(Controls));
		if(controlsTable[i] == NULL)
		{
			fprintf(stderr, "Probleme lors de l'allocation de la liste");
		}
	}
}

int controls_create(char* action_name, int key_number)
{
	if(controlsTable[numberOfControls] == NULL)
	{
		fprintf(stderr, "Failed to set control number %d.\n", numberOfControls);
		return -1;
	}
	else
	{
		controlsTable[numberOfControls]->action_name = action_name;
		controlsTable[numberOfControls]->key_number = key_number;
		controlsTable[numberOfControls]->key_state = -1;
		numberOfControls++;
		return 0;
	}
}

int controls_destroy(char* control_name)
{
	int i, j;
	for(i=0;i < numberOfControls;++i)
	{
		if(strcmp(controlsTable[i]->action_name, control_name) == 0)
		{
			free(controlsTable[i]);
			for(j=i;j < numberOfControls - 1;++j)
			{
				controlsTable[j] = controlsTable[j+1];
			}
			numberOfControls--;
			return 0;
		}
	}
	fprintf(stderr, "Trying to remove a nonexistent control.\n");
	return -1;
}

void controls_save(char* path) {
	int i;
	FILE* file = fopen(path, "w");
	if(!file) {
		printf("Error : Cannot save controls file %s\n", path);
		return;
	}
	fprintf(file, "%d\n", numberOfControls);
	for(i=0; i<numberOfControls; i++) {
		fprintf(file, "%d %s\n", controlsTable[i]->key_number, controlsTable[i]->action_name);
	}
	fclose(file);
}

void controls_load(char* path) {
	int i, key, nb;
	char* name = NULL;
	FILE* file = fopen(path, "w");
	if(!file) {
		printf("Error : Cannot load controls file %s\n", path);
		return;
	}
	fscanf(file, "%d\n", &nb);
	for(i=0; i<nb; i++) {
		fscanf(file, "%d %s\n", &key, name);
		controls_create(name, key);
	}
	fclose(file);
}
