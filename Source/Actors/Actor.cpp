#include "EosStd.h"
#include "Actor.h"
#include "ActorComponent.h"

Actor::Actor(ActorId id) {
	m_id = id;
	m_type = "Unknown";
}

Actor::~Actor(void) {

}

bool Actor::Init() {
	m_type = "TestActor";
	return true;
}

void Actor::Destroy(void) {
	m_components.clear();
}

void Actor::Update(int deltaMs) {
	for (ActorComponents::iterator it = m_components.begin(); it != m_components.end(); ++it) {
		it->second->VUpdate(deltaMs);
	}
}

void Actor::AddComponent(StrongActorCompPtr pComponent) {
	m_components.insert(std::make_pair(pComponent->VGetId(), pComponent));
}