#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineGame.h>

class Rotator final : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Rotator, ComponentBase)
		COMPONENT_UPDATE(update)

		PROP_PARAM(Float, turn_speed, 90.0f)

protected:
	void update() { node->rotate(0, 0, turn_speed * Unigine::Game::getIFps()); }
};