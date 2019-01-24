#include <math.h>
#include <chrono>
#include <thread>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <cstdio>
//#include "shader.cc"
#include "doodler.h"
#define VSPEED 700
#define GRAVITY 1400.0
#define HACCEL 2000.0

extern double rendertime;
extern unsigned int availabletokens;

bool doodler::platform_underlying() {
	for (int i = 0; i < 20; i++) {
		if (platformspos[i]+30 > x + hspeed * rendertime && platformspos[i]-30 < x + hspeed * rendertime && platformsheight[i] < y && platformsheight[i] > y + vspeed * rendertime) {
			return 1;
		}
	}
       return 0;	
}
void doodler::update() {
	sprite::update();
	//TEXTURE
	
	if (flip) {
		texcoords[0] = 1.0;
		texcoords[2] = 1.0;
		texcoords[4] = 0.0;
		texcoords[6] = 0.0;
	} else {
		texcoords[0] = 0.0;
		texcoords[2] = 0.0;
		texcoords[4] = 1.0;
		texcoords[6] = 1.0;
	}
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), texcoords, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}
doodler::doodler(float setx, float sety, float lenght, float height): sprite(setx, sety, lenght, height) {
	flip = 0;
	vspeed = VSPEED;
	hspeed = 0;
	doodler::textureLoad("doodler.png");
}
doodler::~doodler(){}; 
void doodler::move(int8_t direction) {
	if (y + vspeed * rendertime < 240)
		y += vspeed * rendertime;
	vspeed -= GRAVITY*rendertime;
	if (y <= 0 || platform_underlying()) {
		y = abs(y);
		vspeed = VSPEED;
	}
	
	if (direction == 1 && hspeed < HACCEL)
		hspeed += HACCEL * rendertime;
	else if (direction == -1 && hspeed > -HACCEL)
		hspeed -= HACCEL * rendertime;
	else {
		if(hspeed > 0) {
			hspeed -= HACCEL * rendertime;
		} else if (hspeed < 0){
			 hspeed += HACCEL * rendertime;
		}
		if ((hspeed > 0 && hspeed < HACCEL * rendertime) || (hspeed < 0 && hspeed > -HACCEL * rendertime))
			hspeed = 0;
	}
	x+=hspeed*rendertime;
	if (x > 640)
		x = 0;
	else if (x < 0)
		x = 640;
	if (hspeed > 0)
		flip = 1;
	else if (hspeed < 0)
		flip = 0;
	doodler::update();
}
void doodler::getheight(int *height, double *speed) {
	*height = y;
	*speed = vspeed * rendertime;
}
