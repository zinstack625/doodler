#include <math.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "shader.cc"
#include "doodler.h"
#define VSPEED 0.4
#define GRAVITY 0.1
bool doodler::platform_underlying() {
	return 0;
}
doodler::doodler(float setx, float sety) {
	x = setx;
	y = sety;
	vspeed = VSPEED;
	hspeed = 0;
	verts = new float[8]{
		-0.5f, -0.5f,
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f
	};
	indices = new unsigned int[6]{
		0, 1, 2,
		0, 2, 3
	};
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), verts, GL_DYNAMIC_DRAW);
	glGenVertexArrays(1, &ebo);
	glBindVertexArray(ebo);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 2*sizeof(float), 0); 
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
void doodler::move(int8_t direction) {
	vspeed -= GRAVITY;
	y += vspeed;
	if (y < -1 || platform_underlying()) {
		y = abs(y);
		vspeed = VSPEED;
	}
	switch (direction) {
		case 1: hspeed += 0.1;
		case -1: hspeed -= 0.1;
		default: if(hspeed > 0) {
				hspeed -= 0.1;
			 } else {
				 hspeed += 0.1;
			 }
	}
	x+=hspeed;
}
void doodler::draw() {
		glLinkProgram(program);
		glUseProgram(program);
		glBindVertexArray(ebo);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
}

