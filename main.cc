#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>
#include "doodler.h"

int main(int argc, char* argv[]) {
	glfwInit();
	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(640, 480, "Hi", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	double currentTime = glfwGetTime();
	doodler* doodler = new class doodler(320, 20);
		while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		doodler->move(0);
		doodler->draw();
			// Measure speed
			nbFrames++;
			currentTime = glfwGetTime();
			if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
				// printf and reset timer
				printf("%f ms/frame\n", 1000.0/double(nbFrames));
				nbFrames = 0;
				lastTime += 1.0;
			}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}	
}
