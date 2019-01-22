#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/gl.h>
#include <stdio.h>
#include <cstdlib>
#include "doodler.h"
#include "background.h"
#include "platform.h"
#include <chrono>
#include <time.h>
#include <thread>
#define FRAMERATE 180
#define PLATWIDTH 80
#define PLATHEIGHT 10
#define DOODLERWIDTH 60
#define DOODLERHEIGHT 60

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
	window = glfwCreateWindow(640, 480, "Doodler", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glewInit();
	int direction = 0;
	
	std::chrono::time_point<std::chrono::high_resolution_clock> lastframe;
	directionptr = &direction;
	glfwSetKeyCallback(window, movecallback);	
	srand(time(nullptr));
	doodler* doodler = new class doodler(rand()%640, rand()%480, DOODLERWIDTH, DOODLERHEIGHT);
	background bg(320, 0, 1280, 960);
	platform* platforms[10];
	for (int i = 0; i < 10; i++)
		platforms[i] = new platform(rand()%640, rand()%480, PLATWIDTH, PLATHEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	lastframe = std::chrono::high_resolution_clock::now();
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		bg.draw();
		for (int i = 0; i < 10; i++) {
			doodler->platformsheight[i] = platforms[i]->getheight();
			doodler->platformspos[i] = platforms[i]->getpos();
			platforms[i]->draw();
		}
		doodler->move(direction);
		doodler->draw();
		rendertime = std::chrono::nanoseconds(std::chrono::high_resolution_clock::now()-lastframe).count()/1000000000.0;
		lastframe = std::chrono::high_resolution_clock::now();
		printf("FPS: %f\n", 1/rendertime);
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(1000-rendertime*1000)/FRAMERATE));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete doodler;
}
