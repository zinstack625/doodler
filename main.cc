#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/gl.h>
#include <stdio.h>
#include <cstdlib>
#include "doodler.h"
#include <chrono>
#include <time.h>
#include <thread>
#define FRAMERATE 180

static int *directionptr;
double rendertime;

void movecallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT)
			*directionptr = -1;
		else if (key == GLFW_KEY_RIGHT)
			*directionptr = 1;
	} else if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT)
			*directionptr = 0;
		else if (key == GLFW_KEY_RIGHT)
			*directionptr = 0;
	}
}

int main(int argc, char* argv[]) {
	glfwInit();
	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(640, 480, "Hi", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glewInit();
	int direction = 0;
	
	std::chrono::time_point<std::chrono::high_resolution_clock> lastframe, now;
	directionptr = &direction;
	glfwSetKeyCallback(window, movecallback);	
	srand(time(nullptr));
	doodler* doodler = new class doodler(rand()%640, rand()%480);
	lastframe = std::chrono::high_resolution_clock::now();
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		doodler->move(direction);
		doodler->draw();
		now = std::chrono::high_resolution_clock::now();
		rendertime = std::chrono::nanoseconds(now-lastframe).count()/1000000000.0;
		lastframe = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(1000-rendertime*1000)/FRAMERATE));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete doodler;
}
