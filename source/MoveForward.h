#pragma once

#include <UnigineComponentSystem.h>
#include <UniginePhysics.h>

class MoveForward : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(MoveForward, ComponentBase)
		COMPONENT_INIT(init)
		COMPONENT_UPDATE(update)
protected:
	void init();
	void update();
private:
	class PlayerProperties* playerProperties;
};
