#ifndef _EOS_RENDERER_H_
#define _EOS_RENDERER_H_
struct SDL_Window;
struct SDL_Renderer;

class EOSRenderer {
public:
	enum ErrorCode {
		SUCCESS,
		EOS_INIT_VIDEO_FAILED,
		EOS_WINDOW_CREATE_FAILED,
		EOS_RENDERER_CREATE_FALED
	};
private:
	int m_nErrorCode;
	SDL_Window* m_pSDLWin;
	SDL_Renderer* m_pSDLRen;
	void init();
public:
	EOSRenderer();
	~EOSRenderer();
	int GetErrorCode();
};
#endif
