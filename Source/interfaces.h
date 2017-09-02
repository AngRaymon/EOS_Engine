#pragma once
//=====================================================================
// Interfaces.h : Defines interface classes used by the engine
//=====================================================================

class Actor;
class ActorComponent;

typedef unsigned int ActorId;
typedef unsigned int ComponentId;

const ActorId INVALID_ACTOR_ID = 0;
const ComponentId INVALID_COMPONENT_ID = 0;

typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::weak_ptr<Actor> WeakActorPtr;
typedef std::shared_ptr<ActorComponent> StrongActorCompPtr;
typedef std::weak_ptr<ActorComponent> WeakActorCompPtr;

class IRenderer {
public:
	virtual void SetClearColor(unsigned char A, unsigned char R, unsigned char G, unsigned char B) = 0;
	virtual int GetErrorCode() = 0;
	virtual void Render() = 0;
};