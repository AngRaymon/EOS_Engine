#include "EosStd.h"
#include "EosEngine.h"
#include "EOS_Renderer.h"
#include "Actors/Actor.h"
#include "Actors/ActorComponent.h"
#include "SDL.h"
#include "EOSLogger.h"

EosEngine::EosEngine() : m_nErrorCode(0) {
	Init();
}

EosEngine::~EosEngine() {
	delete m_pRenderer;
	SDL_Quit();
}

void EosEngine::Init() {
	m_pRenderer = new EOSRenderer();
	if (m_pRenderer->GetErrorCode() != EOSRenderer::SUCCESS) m_nErrorCode = -1;
}

int EosEngine::GetErrorCode() {
	return m_nErrorCode;
}

bool EosEngine::Update() {
	bool running = true;
	SDL_Event e;
	SDL_PollEvent(&e);
	DrawTest();
	switch (e.type) {
	case SDL_QUIT:
		running = false;
		break;
	}
	return running;
}

void EosEngine::DrawTest() {
	m_pRenderer->Render();
}