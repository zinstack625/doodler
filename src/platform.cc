#include "platform.h"


platform::platform(float setx, float sety, float lenght, float height): sprite(setx, sety, lenght, height) {
	platform::textureLoad("platform.png");
}
platform::~platform(){}
int platform::getheight() {
	return y;
}
int platform::getpos() {
	return x;
}
void platform::move(float px) {
	y+=px;
	sprite::update();
}
