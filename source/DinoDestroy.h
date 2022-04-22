#pragma once
#include<UnigineComponentSystem.h>
#include<UniginePhysics.h>

class DinoDestroy : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(DinoDestroy, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutDown);
protected:

	void init();
	void update();
	void destroy(Unigine::BodyPtr body, int num);
	void shutDown();
private:
	PROP_PARAM(File, fracMesh);
	PROP_PARAM(File, fracMeshCrouch);
	PROP_PARAM(Node, camera);
	void* destroyCallBackID;
	Unigine::NodePtr fracDino;
	Unigine::NodePtr fracDinoCrouching;
	Unigine::ObjectMeshStaticPtr mesh;

	class PlayerProperties* playerProperties;
};
