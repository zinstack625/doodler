class sprite {
	protected:
		float *texcoords;
		double *verts, x, y;
		unsigned int *indices, vbo, vao, ebo, tbo, textureid;
		static unsigned int program;
		int texh, texw;
		unsigned char* texture;
		void shadersInit();
		void textureLoad(const char* texname);
		void update();
	public:
		sprite(float setx, float sety);
		~sprite();
		void draw();
};
