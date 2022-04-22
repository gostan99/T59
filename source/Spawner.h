#pragma once

#include <UnigineComponentSystem.h>

class Spawner :public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Spawner, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

protected:
	void init();
	void update();

private:
	Unigine::Math::vec3 lastSpawn;
	PROP_PARAM(Node, dino);
	PROP_PARAM(Int, numObstaclePerSpawn, 3);
	PROP_PARAM(Float, spawnDistance, 8.f);
	PROP_ARRAY(Vec3, spawnPoints);
	PROP_PARAM(Float, maxDistance, 150.f);
	PROP_PARAM(File, nodeRef);
};

class Destroy : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Destroy, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	void setMaxDistance(float value);
	void setStartPos(Unigine::Math::vec3 pos);

protected:
	void init();
	void update();

private:
	Unigine::Math::vec3 startPos;
	float maxDistance = 0;
};