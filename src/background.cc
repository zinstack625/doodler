#include "background.h"
#include <cstdio>


background::background(float setx, float sety, float lenght, float height): sprite(setx, sety, lenght, height) {
	background::textureLoad("background.png");
}
background::~background(){};

