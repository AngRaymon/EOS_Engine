#pragma once

typedef std::string ActorType;

class Actor {
public:
	typedef std::map<ComponentId, StrongActorCompPtr> ActorComponents;
private:
	ActorId m_id;
	ActorComponents m_components;
	ActorType m_type;

public:
	explicit Actor(ActorId id);
	~Actor(void);

	bool Init(void);
	void PostInit(void);
	void Destroy(void);
	void Update(int deltaMs);

	ActorId GetId(void) const {
		return m_id;
	}
	ActorType GetType(void) const {
		return m_type;
	}

	template <class ComponentType>
	std::weak_ptr<ComponentType> GetComponentById(ComponentId id) {
		ActorComponents::iterator it = m_components.find(id);
		if (it != m_components.end()) {
			StrongActorCompPtr pBase(it->second);
			std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));
			std::weak_ptr<ComponentType> pWeakSub(pSub);
			return pWeakSub;
		}
		else {
			return weak_ptr<ComponentType>();
		}
	}

	template <class ComponentType>
	std::weak_ptr<ComponentType> GetComponentByName(const char* name) {
		ComponentId id = ActorComponent::GetIdFromName(name);
		return GetComponentById<ComponentType>(id);
	}

	const ActorComponents* GetComponents() {
		return &m_components;
	}

	void AddComponent(StrongActorCompPtr pComponent);

};