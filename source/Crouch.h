#pragma once

#include <UnigineComponentSystem.h>

class Crouch : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Crouch, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
protected:
	void init();
	void update();
private:
	class PlayerProperties* playerProperties;
};
