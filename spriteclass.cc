#include <math.h>
#include <chrono>
#include <thread>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <cstdio>
#include "shader.cc"
#include "spriteclass.h"
#define VSPEED 1000
#define GRAVITY 2800.0
#define HACCEL 2000.0


unsigned int sprite::program;
extern double rendertime;

void sprite::shadersInit() {
	program = glCreateProgram();
	unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexshader, 1, &vertex_shader, nullptr);
	glShaderSource(fragmentshader, 1, &fragment_shader, nullptr);
	glCompileShader(vertexshader);
	glCompileShader(fragmentshader);
	glAttachShader(program, vertexshader);
	glAttachShader(program, fragmentshader);
	glLinkProgram(program);
}
void sprite::textureLoad(const char* texname) {
	glGenTextures(1, &textureid);
	glBindTexture(GL_TEXTURE_2D, textureid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	texture = SOIL_load_image(texname, &texw, &texh, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texw, texh, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void sprite::update() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//X
	verts[1] = (double)((y-240)/240.0);
	verts[3] = (double)((y-240)/240.0+sheight/480.0);
	verts[5] = (double)((y-240)/240.0+sheight/480.0);
	verts[7] = (double)((y-240)/240.0);
	//Y
	verts[0] = (double)((x-320)/320.0-(slenght/2)/640.0);
	verts[2] = (double)((x-320)/320.0-(slenght/2)/640.0);
	verts[4] = (double)((x-320)/320.0+(slenght/2)/640.0);
	verts[6] = (double)((x-320)/320.0+(slenght/2)/640.0);
	//OFFLOAD
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(double), verts, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
sprite::sprite(float setx, float sety, float lenght, float height) {
	sprite::shadersInit();
	x = setx;
	y = sety;
	slenght = lenght;
	sheight = height;
	verts = new double[8]{
		//X	Y
		(double)((x-320)/320.0-(slenght/2)/640.0),	(double)((y-240)/240.0),
		(double)((x-320)/320.0-(slenght/2)/640.0),	(double)((y-240)/240.0+sheight/480.0),
		(double)((x-320)/320.0+(slenght/2)/640.0),	(double)((y-240)/240.0+sheight/480.0),
		(double)((x-320)/320.0+(slenght/2)/640.0),	(double)((y-240)/240.0)
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
sprite::~sprite() {
	delete[] texcoords;
       	delete[] verts;
       	delete[] indices;
}
void sprite::draw() {
	glUseProgram(program);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, textureid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

