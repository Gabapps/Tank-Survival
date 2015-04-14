/*
 * Tank.h
 *
 *  Created on: 17 mars 2015
 *      Author: Gabriel
 */

#ifndef SCRIPTS_TANK_H_
#define SCRIPTS_TANK_H_

typedef struct Tank {
	define_script(Tank);
	float speed;
	int life;
	int player;
} Tank;

void tank_setup(Tank* tank, SceneObject* so) {

	so->mesh = ressources_get_mesh(MESH_TANK);
	so->shader = ressources_get_shader(SHADER_TEXTURE);
	so->texture = ressources_get_texture(TEXTURE_TANK);
	tank->speed=1;
	tank->life=100;
}

void tank_run(Tank* tank, SceneObject* so) {
	vec3 v = {tank->speed,0,0};
	vec3_scale(v,v,Time.deltaTime);


	if(input_keypressed_index(5*tank->player+3)) //rotation horaire
	{
		//On commence la manoeuvre
		transform_rotateY(&(so->transform), -Time.deltaTime);

		node_so *iterator = Game.scene->sceneObjects->root;
		while(iterator != NULL) //Tant qu'on a pas testé tous les so de la scene
		{
			if(so!=iterator->value && iterator->value->collider != NULL) //On ne teste pas la collision du so avec lui même
			{
				if(so_collision(so, iterator->value) != NULL)
				{
					if(!strcmp(so_collision(so, iterator->value)->name, "Tank"))
					{
						//Si collision avec un tank, on annule la manoeuvre (rotation dans le sense inverse)
						transform_rotateY(&(so->transform), Time.deltaTime);
					}
					else if(!strcmp(so_collision(so, iterator->value)->name, "Wall"))
					{
						//Si collision avec un wall, on annule la manoeuvre (rotation dans le sense inverse)
						transform_rotateY(&(so->transform), Time.deltaTime);
					}
					else if(!strcmp(so_collision(so, iterator->value)->name, "Bullet"))
					{
						//on ne fait rien. Cas géré dans le bullet_run
					}
				}
			}
				iterator = iterator->next;
			}
		}



	if(input_keypressed_index(5*tank->player+2)) //rotation antihoraire
	{
		transform_rotateY(&(so->transform), Time.deltaTime);

		node_so *iterator = Game.scene->sceneObjects->root;
		while(iterator != NULL)
		{
			if(so!=iterator->value && iterator->value->collider != NULL)
			{
				if(so_collision(so, iterator->value) != NULL)
				{
					if(!strcmp(so_collision(so, iterator->value)->name, "Tank"))
					{
						transform_rotateY(&(so->transform), -Time.deltaTime);
					}
					else if(!strcmp(so_collision(so, iterator->value)->name, "Wall"))
					{
						transform_rotateY(&(so->transform), -Time.deltaTime);
					}
					else if(!strcmp(so_collision(so, iterator->value)->name, "Bullet"))
					{
					}
				}
			}
				iterator = iterator->next;
			}
		}


	if(input_keypressed_index(5*tank->player)) //marche avant
	{
		transform_translate(&(so->transform), v);

		node_so *iterator = Game.scene->sceneObjects->root;
		while(iterator != NULL)
		{
			if(so!=iterator->value && iterator->value->collider != NULL)
			{
				if(so_collision(so, iterator->value) != NULL)
				{
					if(!strcmp(so_collision(so, iterator->value)->name, "Tank"))
					{
						vec3_scale(v,v,-1.0f);
						transform_translate(&(so->transform), v);
					}
					else if(!strcmp(so_collision(so, iterator->value)->name, "Wall"))
					{
						vec3_scale(v,v,-1.0f);
						transform_translate(&(so->transform), v);
					}
					else if(!strcmp(so_collision(so, iterator->value)->name, "Bullet"))
					{
					}
				}
			}
			iterator = iterator->next;
		}
	}


	else if(input_keypressed_index(5*tank->player+1)) //marche arrière
	{
		vec3_scale(v,v,-0.5f);
		transform_translate(&(so->transform), v);

		node_so *iterator = Game.scene->sceneObjects->root;
		while(iterator != NULL)
		{
			if(so!=iterator->value && iterator->value->collider != NULL)
			{
				if(so_collision(so, iterator->value) != NULL)
				{
					if(!strcmp(so_collision(so, iterator->value)->name, "Tank"))
					{
						vec3_scale(v,v,-1.0f);
						transform_translate(&(so->transform), v);
					}
					else if(!strcmp(so_collision(so, iterator->value)->name, "Wall"))
					{
						vec3_scale(v,v,-1.0f);
						transform_translate(&(so->transform), v);
					}
					else if(!strcmp(so_collision(so, iterator->value)->name, "Bullet"))
					{
					}
				}
			}
			iterator = iterator->next;
		}
	}


}

#endif /* SCRIPTS_TANK_H_ */
