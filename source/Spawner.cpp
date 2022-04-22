#include "Spawner.h"

#include <UnigineGame.h>
#include <UnigineSet.h>

REGISTER_COMPONENT(Spawner)
REGISTER_COMPONENT(Destroy)
using namespace Unigine;

void Spawner::init()
{
	lastSpawn = node->getWorldPosition();
	if (dino)
	{
		node->setParent(dino->getChild(0));
	}
}

void Spawner::update()
{
	if (Math::distance(node->getWorldPosition(), lastSpawn) >= spawnDistance)
	{
		Set<int> indexesSet;

		while (indexesSet.size() < numObstaclePerSpawn)
		{
			int index = Math::randInt(0, spawnPoints.size());
			indexesSet.append(index);
		}

		Vector<int> indexes;
		indexesSet.getKeys(indexes);
		auto itr = indexes.begin();
		for (size_t i = 0; i < numObstaclePerSpawn; i++)
		{
			auto obstacle = World::loadNode(nodeRef);
			obstacle->setWorldPosition(spawnPoints[indexes[i]] + node->getWorldPosition());

			auto destroyCmp = ComponentSystem::get()->addComponent<Destroy>(obstacle);
			destroyCmp->setMaxDistance(maxDistance);
			destroyCmp->setStartPos(obstacle->getWorldPosition());
		}

		auto nodePos = node->getWorldPosition();
		lastSpawn = node->getWorldPosition();
		spawnDistance = Math::randFloat(8.f, 20.f);
	}
}

void Destroy::init()
{
	if (node)
	{
		startPos = node->getWorldPosition();
	}
}

void Destroy::update()
{
	if (Math::distance(node->getWorldPosition(), startPos) >= maxDistance)
	{
		node->deleteLater();
	}
}

void Destroy::setMaxDistance(float value)
{
	maxDistance = value;
}

void Destroy::setStartPos(Unigine::Math::vec3 pos)
{
	startPos = pos;
}