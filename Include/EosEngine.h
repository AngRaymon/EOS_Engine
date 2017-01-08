#ifndef _EOSAPP_H_
#define _EOSAPP_H_
#include "EOS_Renderer.h"

struct SDL_Window;
struct SDL_Renderer;

class EosEngine
{
private:
	int m_nErrorCode;
	EOSRenderer* m_pRenderer;

public:
	EosEngine();
	~EosEngine();
	int GetErrorCode();
	void Init();
	bool Update();
};
#endif