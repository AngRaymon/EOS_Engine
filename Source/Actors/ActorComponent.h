#pragma once

class ActorComponent {
protected:
	StrongActorPtr m_pOwner;

public:
	virtual ~ActorComponent(void) { 
		m_pOwner.reset(); 
	}
	virtual bool VInit() = 0;
	virtual void VUpdate(int deltaMs) { }

	virtual ComponentId VGetId(void) const {
		return GetIdFromName(VGetName());
	}
	virtual const char *VGetName() const = 0;
	static ComponentId GetIdFromName(const char* componentStr) {
		//TODO: implement
		return static_cast<ComponentId>(0);
	}

private:
	void SetOwner(StrongActorPtr pOwner) {
		m_pOwner = pOwner;
	}
};