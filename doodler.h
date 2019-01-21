class doodler {
	private:
		float *texcoords;
		double *verts, vspeed, hspeed, x, y;
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
		~doodler();
		void move(int8_t direction);
		void draw();
};
