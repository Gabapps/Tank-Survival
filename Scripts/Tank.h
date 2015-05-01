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
	so->collider = collider_create(0.27, 0.49);
	tank->speed=1;
	tank->life=150;
}

void tank_run(Tank* tank, SceneObject* so) {
	vec3 v = {tank->speed,0,0};
	vec3_scale(v,v,Time.deltaTime);

	//On sauvegarde l'état avant transformation
	Transform backup = so->transform;

	//On bouge
	if(input_keypressed_index(5*tank->player+3)) {
		transform_rotateY(&(so->transform), -Time.deltaTime);
	}
	if(input_keypressed_index(5*tank->player+2)) {
			transform_rotateY(&(so->transform), Time.deltaTime);
	}
	if(input_keypressed_index(5*tank->player)) {
		transform_translate(&(so->transform), v);
	}
	else if(input_keypressed_index(5*tank->player+1)) {
		vec3_scale(v,v,-0.7f);
		transform_translate(&(so->transform), v);
	}

	node_so *iterator = Game.scene->sceneObjects->root;
	while(iterator != NULL) //Tant qu'on a pas testé tous les so de la scene
	{
		// Si le so vérifié a un collider et que ce n'est pas le tank lui-même
		if(iterator->value->collider && iterator->value!=so) {
			SceneObject *collision_so = so_collision(so, iterator->value);
			if(collision_so!= NULL)
			{
				if(strcmp(collision_so->name, "Tank") == 0)
				{
					//On annule le mouvement
					so->transform = backup;
				}
				else if(strcmp(collision_so->name, "Wall") == 0)
				{
					//On annule le mouvement
					so->transform = backup;
				}
			}
		}
		iterator = iterator->next;
	}

}

#endif /* SCRIPTS_TANK_H_ */
