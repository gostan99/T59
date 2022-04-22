#include "FracDino.h"
#include "PlayerProperties.h"

REGISTER_COMPONENT(FracDino)
using namespace Unigine;

void FracDino::init()
{
	if (node)
	{
		if (dino)
		{
			playerProperties = ComponentSystem::get()->getComponentInChildren<PlayerProperties>(dino);
		}
		node->getObjectBodyRigid()->setEnabled(false);
	}
}

void FracDino::update()
{
	if (!playerProperties->mesh->isEnabled() && !applied)
	{
		node->getObjectBodyRigid()->setEnabled(true);
		this->node->getObjectBodyRigid()->addLinearImpulse(dino->getWorldDirection(Math::AXIS::AXIS_Y) * Math::randDirection() * playerProperties->moveForwardSpeed);
		applied = true;
	}
}