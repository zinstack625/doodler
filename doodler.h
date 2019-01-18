class doodler {
	private:
		float x, y, vspeed, hspeed, *verts;
		unsigned int *indices, vbo, ebo, program, textureid;
		int texh, texw;
		unsigned char* texture;
		bool platform_underlying();
		void shadersInit();
		void textureLoad();
	public:
		doodler(float setx, float sety);
		void move(int8_t direction);
		void draw();
};
