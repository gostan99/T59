#include "Turn.h"
#include "PlayerProperties.h"

#include <UnigineLog.h>
#include <UnigineConsole.h>
#include <UnigineInput.h>
#include <UnigineGame.h>

REGISTER_COMPONENT(Turn)

using namespace Unigine;

void Turn::init()
{
	if (node)
	{
		// Get PlayerProperties component
		playerProperties = ComponentSystem::get()->getComponent<PlayerProperties>(node);
		if (!playerProperties)
		{
			Log::error(String::format("%s does not have PlayerProperties component", node->getName()));
		}

		float distanceBetweenLane = 2;
		float origin = node->getWorldPosition().x;
		float lane = origin - distanceBetweenLane * (numLanes / 2);
		for (size_t i = 0; i < numLanes; i++)
		{
			lanes[i] = lane;
			lane += distanceBetweenLane;
		}
	}

	if (!target)
	{
		Log::error("Turn component: target param field is null!");
	}
}

void Turn::update()
{
	if (!Console::isActive())  // do not process input if the console is shown
	{
		inputHandler();
	}

	if (target && !canTurn)
	{
		target->worldTranslate(turnDir * playerProperties->turnSpeed * Game::getIFps());
		if (turnDir != Math::vec3_left)
		{
			if (target->getWorldPosition().x > lanes[currentLane])
			{
				float x = lanes[currentLane];
				float y = target->getWorldPosition().y;
				float z = target->getWorldPosition().z;
				target->setWorldPosition(Math::vec3(x, y, z));
				canTurn = true;
			}
		}
		else
		{
			if (target->getWorldPosition().x < lanes[currentLane])
			{
				float x = lanes[currentLane];
				float y = target->getWorldPosition().y;
				float z = target->getWorldPosition().z;
				target->setWorldPosition(Math::vec3(x, y, z));
				canTurn = true;
			}
		}
	}
}

void Turn::inputHandler()
{
	if (canTurn)
	{
		if (Input::isKeyPressed(Input::KEY::KEY_A))
		{
			currentLane - 1 < 0 ? 0 : --currentLane;
			turnDir = node->getWorldDirection(Math::AXIS::AXIS_NX);
			canTurn = false;
		}
		if (Input::isKeyPressed(Input::KEY::KEY_D))
		{
			currentLane + 1 >= numLanes ? numLanes - 1 : ++currentLane;
			turnDir = node->getWorldDirection(Math::AXIS::AXIS_X);
			canTurn = false;
		}
	}
}