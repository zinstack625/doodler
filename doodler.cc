#include <math.h>
#include <chrono>
#include <thread>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <cstdio>
//#include "shader.cc"
#include "doodler.h"
#define VSPEED 1000
#define GRAVITY 2800.0
#define HACCEL 2000.0

extern double rendertime;

bool doodler::platform_underlying() {
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
doodler::doodler(float setx, float sety): sprite(setx, sety) {
	x = setx;
	y = sety;
	flip = 0;
	vspeed = VSPEED;
	hspeed = 0;
	verts = new double[8]{
		//X	Y
		(double)((x-320)/320.0-30.0/640.0),	(double)((y-240)/240.0),
		(double)((x-320)/320.0-30.0/640.0),	(double)((y-240)/240.0+60.0/480.0),
		(double)((x-320)/320.0+30.0/640.0),	(double)((y-240)/240.0+60.0/480.0),
		(double)((x-320)/320.0+30.0/640.0),	(double)((y-240)/240.0)
	};
	indices = new unsigned int[6]{
		0, 1, 2,
		0, 2, 3
	};
	texcoords = new float[8] {
		0.0,	1.0,
		0.0,	0.0,
		1.0,	0.0,
		1.0,	1.0
	};
	doodler::textureLoad("doodler.png");
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(double), verts, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 2, GL_DOUBLE, false, 2*sizeof(double), 0); 
			glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		glGenBuffers(1, &tbo);
		glBindBuffer(GL_ARRAY_BUFFER, tbo);
			glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), texcoords, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 2, GL_FLOAT, false, 2*sizeof(float), 0);
			glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBindVertexArray(0);
}
doodler::~doodler(){}; 
void doodler::move(int8_t direction) {
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
	printf("%f\n FPS", 1/rendertime);
	doodler::update();
}
