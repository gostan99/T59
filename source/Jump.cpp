#include "Jump.h"
#include "PlayerProperties.h"
#include "VoxAnimator.h"

#include <UnigineInput.h>
#include <UnigineConsole.h>
#include <UnigineGame.h>

REGISTER_COMPONENT(Jump)
using namespace Unigine;

void Jump::init()
{
	if (node)
	{
		// Get PlayerProperties component
		playerProperties = ComponentSystem::get()->getComponent<PlayerProperties>(node);
		if (!playerProperties)
		{
			Log::error(String::format("%s does not have PlayerProperties component", node->getName()));
		}
	}

	if (!target)
	{
		Log::error("Jump component: target param field is null!");
	}
	else
	{
		zCoordOrigin = target->getWorldPosition().z;
	}

	if (!mesh)
	{
		Log::error("Jump component: mesh param field is null!");
	}
	else
	{
		if (!playerProperties)
		{
			Log::error(String::format("%s does not have Animator component", mesh->getName()));
		}
	}
}

void Jump::update()
{
	if (!Console::isActive())
	{
		if (Input::isKeyPressed(Input::KEY::KEY_W) && canJump)
		{
			velocity = node->getWorldDirection(Math::AXIS::AXIS_Z) * playerProperties->jumpForce;
			canJump = false;
			if (playerProperties->mesh)
			{
				auto animator = ComponentSystem::get()->getComponent<VoxAnimator>(playerProperties->mesh);
				animator->playAnimation("jump");
			}
		}
	}
	if (!canJump)
	{
		target->worldTranslate(velocity * Game::getIFps());
		velocity += playerProperties->gravity.get() * Game::getIFps();

		if (target->getWorldPosition().z <= zCoordOrigin)
		{
			float x = target->getWorldPosition().x;
			float y = target->getWorldPosition().y;
			float z = zCoordOrigin;
			target->setWorldPosition(Math::vec3(x, y, z));
			canJump = true;

			if (playerProperties->mesh)
			{
				auto animator = ComponentSystem::get()->getComponent<VoxAnimator>(playerProperties->mesh);
				if (!Input::isKeyPressed(Input::KEY::KEY_S))
					animator->playAnimation("run");
			}
		}
	}
}