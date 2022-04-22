#pragma once

#include <UnigineComponentSystem.h>
#include <UniginePhysics.h>

class Turn : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Turn, ComponentBase)
		COMPONENT_INIT(init)
		COMPONENT_UPDATE(update)

		PROP_PARAM(Node, target)
protected:
	void init();
	void update();
	void inputHandler();
private:
	class PlayerProperties* playerProperties;
	Unigine::Math::vec3 turnDir = Unigine::Math::vec3_left;
	static constexpr int numLanes = 3;
	int currentLane = numLanes / 2;		// Always start in the midle
	float lanes[numLanes];
	bool canTurn = true;
};
