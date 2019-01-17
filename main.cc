#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>
//#include "shader.cc"
#include "doodler.h"

//unsigned int program;

// void initShaders() {
// 	unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER);
// 	unsigned int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
// 	glShaderSource(vertexshader, 1, &vertex_shader, nullptr);
// 	glShaderSource(fragmentshader, 1, &fragment_shader, nullptr);
// 	glCompileShader(vertexshader);
// 	glCompileShader(fragmentshader);
// 	glAttachShader(program, vertexshader);
// 	glAttachShader(program, fragmentshader);
// }


int main(int argc, char* argv[]) {
	glfwInit();
	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(640, 480, "Hi", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
	doodler* doodler = new class doodler(0, 0);
	// float verts[8] {
	// 	-0.5f, -0.5f,
	// 	-0.5f,  0.5f,
	// 	 0.5f,  0.5f,
	// 	 0.5f, -0.5f
	// };
	// unsigned int indices[6] {
	// 	0, 1, 2,
	// 	0, 2, 3
	// };
	// unsigned int vbo = 0, vao = 0;
	// glGenBuffers(1, &vbo);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), verts, GL_DYNAMIC_DRAW);
	// glGenVertexArrays(1, &vao);
	// glBindVertexArray(vao);
	// glEnableVertexAttribArray(0);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// glVertexAttribPointer(0, 2, GL_FLOAT, false, 2*sizeof(float), 0); 
	// program = glCreateProgram();
	// initShaders();
	// glLinkProgram(program);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(program);
		//glBindVertexArray(vao);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
		doodler->draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}	
}
