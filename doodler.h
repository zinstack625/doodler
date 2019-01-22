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
		int platformsheight[10], platformspos[10];
		doodler(float setx, float sety, float lenght, float height);
		~doodler();
		void move(int8_t direction);
};
