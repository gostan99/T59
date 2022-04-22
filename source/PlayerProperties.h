#pragma once
#include <UnigineComponentSystem.h>

class PlayerProperties : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(PlayerProperties, ComponentBase);
	COMPONENT_INIT(init);

	PROP_PARAM(Node, mesh);
	PROP_PARAM(Float, moveForwardSpeed, 10.f);
	PROP_PARAM(Float, turnSpeed, 9.43f);
	PROP_PARAM(Float, jumpForce, 18.f);
	PROP_PARAM(Vec3, gravity, Unigine::Math::vec3(0, 0, -56.47));
protected:
	void init();
};
