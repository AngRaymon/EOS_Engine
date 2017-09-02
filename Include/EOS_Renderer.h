#ifndef _EOS_RENDERER_H_
#define _EOS_RENDERER_H_
struct SDL_Window;
struct SDL_Renderer;
typedef void* SDL_GLContext;

class EOSRenderer : public IRenderer {
public:
	enum ErrorCode {
		SUCCESS,
		EOS_INIT_VIDEO_FAILED,
		EOS_WINDOW_CREATE_FAILED,
		EOS_RENDERER_CREATE_FALED,
		EOS_GL_CONTEXT_CREATE_FAILED,
		EOS_GLEW_INIT_FAILED,
		EOS_VERTEX_SHADER_ERROR,
		EOS_FRAGMENT_SHADER_ERROR,
		EOS_SHADER_LINK_ERROR,
		EOS_VERTEX_ATRRIB_ERROR
	};
private:
	int m_nErrorCode;
	unsigned int m_nGLProgram;
	int m_nGLVertexAttrib;
	SDL_Window* m_pSDLWin;
	SDL_Renderer* m_pSDLRen;
	SDL_GLContext m_SDLGLContext;
	int initGL();
public:
	EOSRenderer();
	~EOSRenderer();
	void init();
	int GetErrorCode();
	void SetClearColor(unsigned char A, unsigned char R, unsigned char G, unsigned char B);
	void Render();
};
#endif
