/*
 * Input.c
 *
 * Created on: 8 mars 2015
 * Author: Nicolas
 */

#include "Input.h"

Controls* controlsTable[20];

/*
 * Regarde l'état des touches dans contrôle et vient modifier l'état du statut
 * des touches en fonctions de si elles sont appuyées ou non
 */
void input_update()
{
	/*
	 * Regarde toutes les touches actives (associées à des actions)
	 * et modifie le state des "controls"
	 */
	int i;

	extern int numberOfControls;
	for(i=0; i<numberOfControls; i++)
	{
		/*controlsTable[i]->key_state = input_keypressed(controlsTable[i]->action_name);*/
		controlsTable[i]->key_state = glfwGetKey(window_get(), controlsTable[i]->key_number);
	}
}
/*
 * Associe une touche à un contrôle
 */
/*
void input_set_controls()
{
}
 */
/*
 * Récupère un Controls_s à partir de son nom
 */
Controls* input_get_controls(char* nom_control)
{
	int i;
	extern int numberOfControls;
	for(i=0; i<numberOfControls; i++)
	{
		if(strcmp(nom_control, controlsTable[i]->action_name) == 0)
		{
			return controlsTable[i];
		}
	}
	fprintf(stderr, "Nonexistent key name");
	return NULL;
}

Controls* input_get_controls_index(int key_number)
{
	return controlsTable[key_number];
}

/*
 * rend l'état de la touche demandée (vraie si appuyée)
 * ex : if(keypresse(player1, up))
 */
int input_keypressed(char* nom_control)
{
	return ((input_get_controls(nom_control))->key_state) == GLFW_PRESS;
}

int input_keypressed_index(int key)
{
	return ((input_get_controls_index(key))->key_state) == GLFW_PRESS;
}
