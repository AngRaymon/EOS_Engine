#include "EOS_Renderer.h"
#include "SDL.h"

EOSRenderer::EOSRenderer() : m_nErrorCode(0) {
	init();
}

EOSRenderer::~EOSRenderer() {
	if (m_pSDLRen) SDL_DestroyRenderer(m_pSDLRen);
	if (m_pSDLWin) SDL_DestroyWindow(m_pSDLWin);
}

void EOSRenderer::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		m_nErrorCode = EOS_INIT_VIDEO_FAILED;
	}
	m_pSDLWin = SDL_CreateWindow("Hello World", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (m_pSDLWin == nullptr) {
		m_nErrorCode = EOS_WINDOW_CREATE_FAILED;
		return;
	}
	m_pSDLRen = SDL_CreateRenderer(m_pSDLWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pSDLRen == nullptr) {
		SDL_DestroyWindow(m_pSDLWin);
		m_nErrorCode = EOS_RENDERER_CREATE_FALED;
		return;
	}
}

int EOSRenderer::GetErrorCode() {
	return m_nErrorCode;
}