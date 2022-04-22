#pragma once

#include <UnigineComponentSystem.h>
#include <UniginePhysics.h>
class FracDino : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(FracDino, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

protected:
	void init();
	void update();
private:
	PROP_PARAM(Node, dino);
	class PlayerProperties* playerProperties;
	bool applied = false;
};
