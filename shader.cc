const char* vertex_shader = 
	"#version 330 core\n"
	"in vec2 position;\n"
	"void main() {\n"
	"	gl_Position = vec4(position, 0.0, 1.0);\n"
	"}\n";

const char* fragment_shader = 
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main() {\n"
	"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
	"}\n";
