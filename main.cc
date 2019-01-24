#include <GL/glew.h>
#include <GL/freeglut.h>
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
#define MAXPLATS 20



static int *directionptr;
double rendertime;
unsigned int availabletokens = MAXPLATS;
 static int direction = 0;
 static int doodlerheight = 0;
 static double doodlerspeed = 0;
 static std::chrono::time_point<std::chrono::high_resolution_clock> lastframe;
 static doodler* doodler;
 static background* bg;
 static unsigned int score;
 static platform* platforms[MAXPLATS];


void movecallback(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT)
		direction = -1;
	else if (key == GLUT_KEY_RIGHT)
		direction = 1;
}
void stopcallback(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT)
		direction = 0;
	else if (key == GLUT_KEY_RIGHT)
		direction = 0;

}
 
void drawFunc();

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE );
	glutInitContextVersion(3,3);
	int window = glutCreateWindow("Doodler");
	glewInit();
	doodler  = new class doodler(rand()%640, rand()%480%200, DOODLERWIDTH, DOODLERHEIGHT);
	bg = new class background(320, 0, 1280, 960);
	score = 0;
	srand(time(nullptr));
	// Init platforms
 	for (int i = 0; i < MAXPLATS; i++) {
 		platforms[i] = new platform(rand()%640, rand()%480, PLATWIDTH, PLATHEIGHT);
 		availabletokens--;
 	}
 
 	// Destroy impossible platforms
 	int higher = 640;
 	for (int i = 0; i < MAXPLATS; i++) {
 		while (higher - platforms[i]->getheight() > 220) {
 			for (int o = 0; o < MAXPLATS; o++) {
 				if (platforms[o] == nullptr)
 					continue;
 				if (platforms[i] == nullptr)
 					break;
 				if (platforms[o]->getheight() > platforms[i]->getheight() && platforms[o]->getheight() < higher)
 					higher = platforms[o]->getheight();
 			}
 			if (higher - platforms[i]->getheight() < 220)
 				break;
 			delete platforms[i];
 			platforms[i] = new platform(rand()%640, rand()%480, PLATWIDTH, PLATHEIGHT);
 		}
 		higher = 480;
 	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	lastframe = std::chrono::high_resolution_clock::now();
	glutDisplayFunc(drawFunc);
	glutIdleFunc(drawFunc);
	glutSpecialFunc(movecallback);
	glutSpecialUpFunc(stopcallback);
	glutMainLoop();


	delete doodler;
	delete bg;
	for (int i = 0; i < MAXPLATS; i++)
		delete platforms[i];
}
void drawFunc() {
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 		bg->draw();
 		doodler->getheight(&doodlerheight, &doodlerspeed);
		if (score > 10000) 
 			availabletokens=1;
		if (score > 20000)
			availabletokens = 2;
		if (score > 30000)
			availabletokens = 3;
		if (score > 40000)
			availabletokens = 4;
		if (score > 50000)
			availabletokens = 5;
		if (score > 60000)
			availabletokens = 6;
		if (score > 70000)
			availabletokens = 7;
		if (score > 80000)
			availabletokens = 8;
		if (score > 90000)
			availabletokens = 9;
		if (score > 100000)
			availabletokens=10;
 		for (int i = 0; i < MAXPLATS; i++) {
 			if (doodlerheight + doodlerspeed > 238) {
 				platforms[i]->move(-doodlerspeed);
 			}
 			if (platforms[i]->getheight() < 0) {
				if (i <= MAXPLATS - availabletokens)
 					platforms[i] = new platform(rand()%640, rand()%100 + 480, PLATWIDTH, PLATHEIGHT);
 			}
 			doodler->platformsheight[i] = platforms[i]->getheight();
 			doodler->platformspos[i] = platforms[i]->getpos();
 			platforms[i]->draw();
 		}
 		if (doodlerheight + doodlerspeed > 238)
 			score += doodlerspeed;
 		doodler->move(direction);
 		doodler->draw();
 		rendertime = std::chrono::nanoseconds(std::chrono::high_resolution_clock::now()-lastframe).count()/1000000000.0;
 		lastframe = std::chrono::high_resolution_clock::now();
 		printf("FPS: %f, Score:%i\n", 1/rendertime, score);
 		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(1000-rendertime*1000)/FRAMERATE));
		glutSwapBuffers();
}
