/*
 * Bullet.h
 *
 *  Created on: 4 avr. 2015
 *      Author: ethel
 */

#ifndef SCRIPTS_BULLET_H_
#define SCRIPTS_BULLET_H_

typedef struct Bullet{
	define_script(Bullet);
	float speed;
	//double  x, y, dx, dy, bullet_phi;
	//int active;
}Bullet;

void bullet_setup(Bullet* bullet, SceneObject* so){
	bullet->speed =2;
}

void bullet_run(Bullet* bullet, SceneObject* so){
	vec3 v = {bullet->speed,0,0};
	vec3_scale(v,v,Time.deltaTime);

	transform_translate(&(so->transform), v);
	printf("%f-%f-%f\n",v[0],v[1],v[2]);

}


#endif /* SCRIPTS_BULLET_H_ */
