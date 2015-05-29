/*
 * SceneScript.h
 *
 *  Created on: 19 mars 2015
 *      Author: Gabriel
 */

#ifndef SCRIPTS_SCENESCRIPT_H_
#define SCRIPTS_SCENESCRIPT_H_

#include <stdio.h>

#include "../Ressources.h"

#include "Tank.h"

#include "Bullet.h"

#include "Wall.h"

#include <math.h>
#include <time.h>

#include "Items.h"



typedef struct SceneScript {
	define_script(SceneScript);
	float spawnpoints[MAX_PLAYER*2]; // 4 spawns with 2 coords each
	float itempoints[8];
	float timeitem;
	int lastvrand;
} SceneScript;

typedef struct MapConf {
	vec3 cam_pos;
	vec3 cam_center;
	int map_size_x, map_size_y;
} MapConf;

void sc_map(SceneScript* scscript, MapConf *map_conf);
void sc_controls();
void sc_loadplayers(SceneScript* scscript);
void get_map_infos(MapConf *map_conf, FILE* map);
void sc_items(SceneScript* scscript);
//ajout de fonctions permettant la gestion de parties
void sc_end_game(SceneScript* scscript);


void sc_setup(SceneScript* scenescript, SceneObject* so) {

	MapConf* map_conf = (MapConf*)malloc(sizeof(MapConf));

	ressources_init();
	ressources_load();

	sc_controls();
	sc_map(scenescript, map_conf);
	sc_loadplayers(scenescript);

	Camera cam;
	camera_init(&cam);
	//vec3 pos = {map_conf->cam_pos[0],map_conf->cam_pos[1],map_conf->cam_pos[2]},
	//		center = {map_conf->cam_center[0],map_conf->cam_center[1],map_conf->cam_center[2]},
	//		up = {0,1,0};

	vec3 up = {0,1,0};
	camera_look_at(&cam, map_conf->cam_pos, map_conf->cam_center, up);
	camera_refresh_matrices(&cam);
	// Day color : {1,0.94,0.5}; force : 0.7
	// Moonlight color :{0,0,0.8}; force : 0.3
	vec3 poslight = {5,30,5},
			dirlight = {-1,-1,-0.1},
			colorlight = {1,0.94,0.5};
	Game.scene->camera = cam;
	Game.scene->light = sunlight_create(poslight, dirlight, colorlight, 0.7);
	//Time.maxfps=-1;

	scenescript->timeitem = 15;
	scenescript->lastvrand = 6;

}

void sc_run(SceneScript* scenescript, SceneObject* so) {
	vec3 dir = {cos(0.1*Time.timeSinceStart),-1,sin(0.1*Time.timeSinceStart)};
	sunlight_set_direction(&(Game.scene->light), dir);

	sc_items(scenescript);

	Camera* cam = &(Game.scene->camera);
	static float delta =0;

	if(death_counter==3 && tank_gagnant != NULL){
		delta +=Time.deltaTime;
		vec3_cpy(cam->target,tank_gagnant->transform.position);

		vec3 pos = {cam->target[0]+8*cosf(delta/2),-0.3*delta+4.5 ,cam->target[2]+6*sinf(delta/2)};
		//il faut que je recupere 15 ( cam->pos depuis la map "au cas où on change de map)
		camera_look_at(cam,pos,cam->target,cam->up);

		if(delta>10){
			delta = 0;
			game_load_scene("Menu"); //apres un certain temps,on arrete de tourner la camera
		}
	}
}


void get_map_infos(MapConf *map_conf, FILE* map)
{
	fscanf(map, "%f %f %f\n", &(map_conf->cam_pos[0]), &(map_conf->cam_pos[1]), &(map_conf->cam_pos[2]));
	fscanf(map, "%f %f %f\n", &(map_conf->cam_center[0]), &(map_conf->cam_center[1]), &(map_conf->cam_center[2]));
	fscanf(map, "%d %d\n", &(map_conf->map_size_x), &(map_conf->map_size_y));
}

void sc_map(SceneScript* scscript, MapConf *map_conf)
{
	int i, j, input;
	Transform transform_map = transform_origin_no_parent();

	SceneObject *map_wall = so_create("Wall", transform_origin_no_parent(NULL));
	SceneObject* wallToAdd;

	FILE* map = fopen("Map/map.txt", "r");
	if (map == NULL)
		fprintf(stderr, "Failed to open map.txt");
	int nbspawn = 0, nbpoints = 0;

	get_map_infos(map_conf, map);

	for(i=0;i<map_conf->map_size_x;++i)
	{
		for(j=0;j<map_conf->map_size_y;++j)
		{
			transform_map = transform_origin_no_parent();
			vec3 vec = {i,0,map_conf->map_size_y-j-1};
			transform_translate(&transform_map, vec);
			fscanf(map, "%d ", &input);
			//Mur indestructible
			if(input == 1)
			{
				Wall *script = malloc(sizeof(Wall));
				script->name = "Wall";
				script->setup = wall_setup;
				script->run = wall_run;
				script->destrutible = 0;
				script->texture = TEXTURE_WALL;
				script->mesh = MESH_WALL;

				wallToAdd = so_duplicate(map_wall, "Wall", transform_map);

				so_add_script(wallToAdd, (Script*)script);
				scene_add_so(Game.scene, wallToAdd);
			}
			//Spawn
			else if(input == 2) {
				scscript->spawnpoints[nbspawn*2]=(float)i;
				scscript->spawnpoints[nbspawn*2+1]=(float)map_conf->map_size_x-j-1;
				nbspawn++;
			}
			//Antichar
			else if(input == 3) {
				Wall *script = malloc(sizeof(Wall));
				script->name = "Wall";
				script->setup = wall_setup;
				script->run = wall_run;
				script->destrutible = 1;
				script->life = 70;
				script->texture = TEXTURE_ANTICHAR;
				script->mesh = MESH_ANTICHAR;

				wallToAdd = so_duplicate(map_wall, "Wall", transform_map);

				so_add_script(wallToAdd, (Script*)script);
				scene_add_so(Game.scene, wallToAdd);
			}
			else if(input == 4) {
				scscript->itempoints[nbpoints*2]=(float)i;
				scscript->itempoints[nbpoints*2+1]=(float)map_conf->map_size_x-j-1;
				nbpoints++;
			}
		}
		fscanf(map, "\n");
	}
	fclose(map);

	SceneObject* ground = so_create("Ground", transform_xyz_no_parent(15,0,15));

	ground->mesh = ressources_get_mesh(MESH_GROUND);
	ground->texture = ressources_get_texture(TEXTURE_GROUND);
	ground->shader = ressources_get_shader(SHADER_TEXTURE);

	SceneObject* sky = so_create("Sky", transform_xyz_no_parent(0,-20,0));
	sky->mesh = ressources_get_mesh(MESH_SKY);
	sky->texture = ressources_get_texture(TEXTURE_SKY);
	sky->shader = ressources_get_shader(SHADER_SKYBOX);

	scene_add_so(Game.scene, ground);
	scene_add_so(Game.scene, sky);

}

void sc_controls() {
	init_controlsTable();

	controls_create("P1_up", GLFW_KEY_UP);
	controls_create("P1_down", GLFW_KEY_DOWN);
	controls_create("P1_left", GLFW_KEY_LEFT);
	controls_create("P1_right", GLFW_KEY_RIGHT);
	controls_create("P1_fire", GLFW_KEY_KP_1);

	controls_create("P2_up", GLFW_KEY_Z);
	controls_create("P2_down", GLFW_KEY_S);
	controls_create("P2_left", GLFW_KEY_Q);
	controls_create("P2_right", GLFW_KEY_D);
	controls_create("P2_fire", GLFW_KEY_E);

	controls_create("P3_up", GLFW_KEY_Y);
	controls_create("P3_down", GLFW_KEY_H);
	controls_create("P3_left", GLFW_KEY_G);
	controls_create("P3_right", GLFW_KEY_J);
	controls_create("P3_fire", GLFW_KEY_U);

	controls_create("P4_up", GLFW_KEY_KP_5);
	controls_create("P4_down", GLFW_KEY_KP_6);
	controls_create("P4_left", GLFW_KEY_KP_3);
	controls_create("P4_right", GLFW_KEY_KP_9);
	controls_create("P4_fire", GLFW_KEY_KP_8);
}

void sc_loadplayers(SceneScript* scscript) {
	int i;
	for(i=0; i<MAX_PLAYER; i++) {
		Tank *script = malloc(sizeof(Tank));
		script->name = "Tank";
		script->setup = tank_setup;
		script->run = tank_run;
		script->player = i;

		SceneObject *tank = so_create("Tank", transform_xyz_no_parent(scscript->spawnpoints[i*2],0,scscript->spawnpoints[i*2+1]));
		so_add_script(tank, (Script*)script);

		Bullet *script_bullet = malloc(sizeof(Bullet));
		script_bullet->name = "Bullet";
		script_bullet->setup = bullet_setup;
		script_bullet->run = bullet_run;

		SceneObject *bullet = so_create("Bullet", transform_xyz_no_parent(0.65,0.35,0));
		so_add_script(bullet, (Script*)script_bullet);
		so_add_child(tank, bullet);
		scene_add_so(Game.scene, tank);
	}

}


void sc_items(SceneScript* scscript)
{
	srand((unsigned int)(Time.timeSinceStart*100000));
	int vrand = rand() % 4;
	scscript->lastvrand = 6;

	if(vrand==scscript->lastvrand) vrand = (vrand+1)%4;
	scscript->timeitem += Time.deltaTime;
	if(scscript->timeitem>10)
	{
		scscript->timeitem = 0;
		activ_items(scscript->itempoints[2*vrand], scscript->itempoints[2*vrand+1]);
	}
	scscript->lastvrand = vrand;
}
void sc_end_game(SceneScript* scscript){

}

#endif /* SCRIPTS_SCENESCRIPT_H_ */
