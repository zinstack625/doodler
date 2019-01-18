const char* vertex_shader = 
	"#version 330 core\n"
	"layout(location=0) in vec2 position;\n"
	"layout(location=1) in vec2 texcoord;\n"
	"void main() {\n"
	"	gl_Position = vec4(position, 0.0, 1.0);\n"
	"}\n";

const char* fragment_shader = 
	"#version 330 core\n"
	"in vec2 texcoord;\n"
	"out vec4 color;\n"
	"uniform sampler2D texture;\n"
	"void main() {\n"
	"	color = texture(texture, texcoord);\n"
	"//	color = vec4(1.0, 1.0, 1.0, 1.0);\n"
	"}\n";
