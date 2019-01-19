class doodler {
	private:
		float *texcoords;
		double rendertime, *verts, vspeed, hspeed, x, y;
		unsigned int *indices, vbo, vao, ebo, tbo, program, textureid;
		int texh, texw;
		unsigned char* texture;
		bool platform_underlying();
		bool flip;
		void shadersInit();
		void textureLoad();
		void update();
	public:
		doodler(float setx, float sety);
		void move(int8_t direction);
		void draw();
};
