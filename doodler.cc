#include <math.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <cstdio>
#include "shader.cc"
#include "doodler.h"
#define VSPEED 15
#define GRAVITY 0.3
bool doodler::platform_underlying() {
	return 0;
}
void doodler::shadersInit() {
	program = glCreateProgram();
	unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexshader, 1, &vertex_shader, nullptr);
	glShaderSource(fragmentshader, 1, &fragment_shader, nullptr);
	glCompileShader(vertexshader);
	glCompileShader(fragmentshader);
	glAttachShader(program, vertexshader);
	glAttachShader(program, fragmentshader);
}
void doodler::textureLoad() {
	glGenTextures(1, &textureid);
	glBindTexture(GL_TEXTURE_2D, textureid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	texture = SOIL_load_image("doodler.png", &texw, &texh, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texw, texh, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}
doodler::doodler(float setx, float sety) {
	x = setx;
	y = sety;
	vspeed = VSPEED;
	hspeed = 0;
	verts = new float[16]{
		//X	Y	TEXX	TEXY
		(float)((x-320)/320.0-30.0/640.0),	(float)((y-240)/240.0),	 0.0,	 1.0,
		(float)((x-320)/320.0-30.0/640.0),	(float)((y-240)/240.0+60.0/480.0),	 0.0,	 0.0,
		(float)((x-320)/320.0+30.0/640.0),	(float)((y-240)/240.0+60.0/480.0),	 1.0,	 0.0,
		(float)((x-320)/320.0+30.0/640.0),	(float)((y-240)/240.0),	 1.0,	 1.0
	};
	indices = new unsigned int[6]{
		0, 1, 2,
		0, 2, 3
	};
	doodler::textureLoad();
	doodler::shadersInit();
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), verts, GL_DYNAMIC_DRAW);
	glGenVertexArrays(1, &ebo);
	glBindVertexArray(ebo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 4*sizeof(float), 0); 
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 4*sizeof(float), reinterpret_cast<void*>(2*sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void doodler::move(int8_t direction) {
	vspeed -= GRAVITY;
	y += vspeed;
	if (y <= 0 || platform_underlying()) {
		y = abs(y);
		vspeed = VSPEED;
	}
	//void update();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	verts[1] = (float)((y-240)/240.0);
	verts[5] = (float)((y-240)/240.0+60.0/480.0);
	verts[9] = (float)((y-240)/240.0+60.0/480.0);
	verts[13] = (float)((y-240)/240.0);
	

	switch (direction) {
		case 1: hspeed += 5;
		case -1: hspeed -= 5;
		default: if(hspeed > 0) {
				hspeed -= 5;
			 } else if (hspeed < 0){
				 hspeed += 5;
			 }
	}
	x+=hspeed;

	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), verts, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void doodler::draw() {
		glLinkProgram(program);
		glUseProgram(program);
		glBindVertexArray(ebo);
		glBindTexture(GL_TEXTURE_2D, textureid);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glUseProgram(0);
}

