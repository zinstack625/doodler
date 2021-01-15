const char* vertex_shader = 
	"#version 330 core\n"
	"layout(location=0) in vec2 position;\n"
	"layout(location=1) in vec2 texcoord;\n"
	"out vec2 Texcoord;\n"
	"void main() {\n"
	"	Texcoord = texcoord;\n"
	"	gl_Position = vec4(position, 0.0, 1.0);\n"
	"}\n";

const char* fragment_shader = 
	"#version 330 core\n"
	"in vec2 Texcoord;\n"
	"out vec4 color;\n"
	"uniform sampler2D text;\n"
	"void main() {\n"
	"	vec4 colortemp = texture(text, Texcoord);\n"
	"	color = colortemp;\n"
	"}\n";
