#include "Crouch.h"
#include "PlayerProperties.h"
#include "VoxAnimator.h"

#include <UnigineInput.h>
#include <UniginePhysics.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(Crouch)
using namespace Unigine;

void Crouch::init()
{
	if (node)
	{
		playerProperties = ComponentSystem::get()->getComponent<PlayerProperties>(node);
		if (!playerProperties)
		{
			Log::error("Crouch component: %s does not have PlayerProperties component", node->getName());
		}
	}
}

Math::vec3 prevGravity;
void Crouch::update()
{
	if (!Console::isActive())
	{
		if (Input::isKeyDown(Input::KEY::KEY_S))
		{
			if (playerProperties->mesh)
			{
				auto animator = ComponentSystem::get()->getComponent<VoxAnimator>(playerProperties->mesh);
				prevGravity = playerProperties->gravity;
				playerProperties->gravity = playerProperties->gravity.get() * 3;
				animator->playAnimation("crouching");
				auto body = playerProperties->mesh->getObjectBodyRigid();
				body->getShape(2)->setEnabled(false);
				body->getShape(3)->setEnabled(true);
			}
		}
		if (Input::isKeyUp(Input::KEY::KEY_S))
		{
			if (playerProperties->mesh)
			{
				auto animator = ComponentSystem::get()->getComponent<VoxAnimator>(playerProperties->mesh);
				animator->playAnimation("run");
				auto body = playerProperties->mesh->getObjectBodyRigid();
				body->getShape(2)->setEnabled(true);
				body->getShape(3)->setEnabled(false);
				playerProperties->gravity = prevGravity;
			}
		}
	}
}