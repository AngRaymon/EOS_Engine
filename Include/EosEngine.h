#ifndef _EOSAPP_H_
#define _EOSAPP_H_

struct SDL_Window;
struct SDL_Renderer;
class IRenderer;

class EosEngine
{
private:
	int m_nErrorCode;
	IRenderer* m_pRenderer;
	void DrawTest();

public:
	EosEngine();
	~EosEngine();
	int GetErrorCode();
	void Init();
	bool Update();
};
#endif