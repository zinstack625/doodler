#include "spriteclass.h"
class doodler: public sprite {
	private:
		double vspeed, hspeed;
		bool platform_underlying();
		bool flip;
		void update();
	public:
		doodler(float setx, float sety);
		~doodler();
		void move(int8_t direction);
};
