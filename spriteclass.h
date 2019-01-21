class sprite {
	protected:
		float *texcoords, slenght, sheight;
		double *verts, x, y;
		unsigned int *indices, vbo, vao, ebo, tbo, textureid;
		static unsigned int program;
		int texh, texw;
		unsigned char* texture;
		void shadersInit();
		void textureLoad(const char* texname);
		void update();
	public:
		sprite(float setx, float sety, float lenght, float height);
		~sprite();
		void draw();
};
