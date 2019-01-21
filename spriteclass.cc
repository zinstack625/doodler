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
	verts[1] = (float)((y-240)/240.0);
	verts[3] = (float)((y-240)/240.0+60.0/480.0);
	verts[5] = (float)((y-240)/240.0+60.0/480.0);
	verts[7] = (float)((y-240)/240.0);
	//Y
	verts[0] = (float)((x-320)/320.0-30.0/640.0);
	verts[2] = (float)((x-320)/320.0-30.0/640.0);
	verts[4] = (float)((x-320)/320.0+30.0/640.0);
	verts[6] = (float)((x-320)/320.0+30.0/640.0);
	//OFFLOAD
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(double), verts, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
sprite::sprite(float setx, float sety) {
	sprite::shadersInit();
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

