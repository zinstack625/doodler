class doodler {
	private:
		float x, y, vspeed, hspeed, *verts;
		unsigned int *indices, vbo, ebo, program;
		bool platform_underlying();
	public:
		doodler(float setx, float sety);
		void move(int8_t direction);
		void draw();
};
