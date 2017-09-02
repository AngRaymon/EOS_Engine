#include "EosStd.h"
#include "EOS_Renderer.h"
#include "SDL.h"
#include "GL/glew.h"
#include "SDL_opengl.h"

static const GLchar* vertexShaderSource[] = {
	"#version 140\n" \
	"in vec2 LVertexPos2D;" \
	"void main() {" \
	"gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );}"
};

static const GLchar* fragmentShaderSource[] = {
	"#version 140\n" \
	"out vec4 LFragment;" \
	"void main() {" \
	"LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
};

EOSRenderer::EOSRenderer() : m_nErrorCode(0) {
	init();
}

EOSRenderer::~EOSRenderer() {
	glDeleteProgram(m_nGLProgram);
	if (m_pSDLRen) SDL_DestroyRenderer(m_pSDLRen);
	if (m_pSDLWin) SDL_DestroyWindow(m_pSDLWin);
	m_pSDLWin = NULL;
}

void EOSRenderer::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		m_nErrorCode = EOS_INIT_VIDEO_FAILED;
		return;
	}
	//Use OpenGl 3.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//Create Window
	m_pSDLWin = SDL_CreateWindow("Hello World", 100, 100, 640, 480, SDL_WINDOW_OPENGL);
	if (m_pSDLWin == nullptr) {
		m_nErrorCode = EOS_WINDOW_CREATE_FAILED;
		return;
	}
	//Create GL Context
	m_SDLGLContext = SDL_GL_CreateContext(m_pSDLWin);
	if (m_SDLGLContext == nullptr) {
		m_nErrorCode = EOS_GL_CONTEXT_CREATE_FAILED;
		return;
	}
	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		m_nErrorCode = EOS_GLEW_INIT_FAILED;
		return;
	}
	//Default Vsync off
	if (SDL_GL_SetSwapInterval(0) < 0) {
		//Nothing currently
		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}
	m_nErrorCode = initGL();
}

//test: remove this
GLuint gVBO = 0;
GLuint gIBO = 0;

int EOSRenderer::initGL() {
	m_nGLProgram = glCreateProgram();
	//Set up vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE) {
		return EOS_VERTEX_SHADER_ERROR;
	}
	glAttachShader(m_nGLProgram, vertexShader);
	//Set up fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	shaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE) {
		return EOS_FRAGMENT_SHADER_ERROR;
	}
	glAttachShader(m_nGLProgram, fragmentShader);
	//Link Program
	glLinkProgram(m_nGLProgram);
	GLint status = GL_TRUE;
	glGetProgramiv(m_nGLProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		return EOS_SHADER_LINK_ERROR;
	}
	//Set up vertex attribs
	m_nGLVertexAttrib = glGetAttribLocation(m_nGLProgram, "LVertexPos2D");
	if (m_nGLVertexAttrib == -1) {
		return EOS_VERTEX_ATRRIB_ERROR;
	}
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//VBO data
	GLfloat vertexData[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	//IBO data
	GLuint indexData[] = { 0, 1, 2, 3 };

	//create VBO
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	//create IBO
	glGenBuffers(1, &gIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

	return 0;
}

int EOSRenderer::GetErrorCode() {
	return m_nErrorCode;
}

void EOSRenderer::SetClearColor(unsigned char A, unsigned char R, unsigned char G, unsigned char B) {

}

void EOSRenderer::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(m_nGLProgram);
	glEnableVertexAttribArray(m_nGLVertexAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glVertexAttribPointer(m_nGLVertexAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(m_nGLVertexAttrib);
	glUseProgram(NULL);
	SDL_GL_SwapWindow(m_pSDLWin);
}