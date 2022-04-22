#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWorlds.h>

class Reposition : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Reposition, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

protected:
	void init();
	void update();

private:
	void enterCallback(Unigine::NodePtr target);
	PROP_PARAM(Float, teleportDistance, 2000.f);

	Unigine::WorldTriggerPtr trigger;
};