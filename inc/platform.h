#ifndef SPRITECLASS
#include "spriteclass.h"
#endif
class platform: public sprite {
	public:
		platform(float setx, float sety, float lenght, float height);
		~platform();
		int getheight();
		int getpos();
		void move(float px);
};
