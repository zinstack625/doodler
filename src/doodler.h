#ifndef SPRITECLASS
#include "spriteclass.h"
#endif

class doodler: public sprite {
	private:
		double vspeed, hspeed;
		bool platform_underlying();
		bool flip;
		void update();
	public:
		int platformsheight[50], platformspos[50];
		doodler(float setx, float sety, float lenght, float height);
		~doodler();
		void move(int8_t direction);
		void getheight(int* height, double *speed);
};
