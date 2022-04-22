#include "MoveForward.h"
#include "PlayerProperties.h"

#include <UnigineLog.h>
#include <UnigineGame.h>
#include <UnigineConsole.h>

REGISTER_COMPONENT(MoveForward)

using namespace Unigine;

float zOriginNode;
float zOriginMesh;
void MoveForward::init()
{
	if (node)
	{
		// Get PlayerProperties component
		playerProperties = ComponentSystem::get()->getComponent<PlayerProperties>(node);
		if (!playerProperties)
		{
			Log::error(String::format("%s does not have PlayerProperties component", node->getName()));
		}
		zOriginNode = node->getWorldPosition().z;
		auto mesh = playerProperties->mesh;
		zOriginMesh = mesh->getWorldPosition().z;
	}
}

void MoveForward::update()
{
	if (playerProperties && node && !Console::isActive())
	{
		// Get moveForwardSpeed from PlayerProperties
		float moveForwardSpeed = playerProperties->moveForwardSpeed;
		// Get forward direction
		Math::Vec3 forwardDir = node->getWorldDirection(MathLib::AXIS::AXIS_Y);
		node->worldTranslate(forwardDir * moveForwardSpeed * Game::getIFps());

		auto mesh = playerProperties->mesh;
		if (node->getWorldPosition().z < zOriginNode || mesh->getOldWorldPosition().z < zOriginMesh)
		{
			node->worldTranslate(Math::vec3_up * zOriginNode);
			mesh->worldTranslate(Math::vec3_up * zOriginMesh);
		}
	}
}