#pragma once

#include <UnigineComponentSystem.h>

class Jump : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Jump, ComponentBase)
		COMPONENT_INIT(init)
		COMPONENT_UPDATE(update)

		PROP_PARAM(Node, target)
		PROP_PARAM(Node, mesh)
protected:
	void init();
	void update();
private:
	class PlayerProperties* playerProperties;
	bool canJump = true;
	float zCoordOrigin = 0;
	Unigine::Math::vec3 velocity = Unigine::Math::vec3_zero;
};