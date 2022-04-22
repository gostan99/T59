#include "DinoDestroy.h"
#include "MoveForward.h"
#include "Turn.h"
#include "Jump.h"
#include "PlayerProperties.h"
#include "VoxAnimator.h"

REGISTER_COMPONENT(DinoDestroy)
using namespace Unigine;

void DinoDestroy::init()
{
	if (node)
	{
		playerProperties = ComponentSystem::get()->getComponent<PlayerProperties>(node);
		if (!playerProperties)
		{
			Log::error("Crouch component: %s does not have PlayerProperties component", node->getName());
			return;
		}
		fracDino = World::loadNode(fracMesh);
		fracDino->setWorldPosition(node->getWorldPosition() + Math::vec3_back * 10);
		fracDino->setParent(node);

		fracDinoCrouching = World::loadNode(fracMeshCrouch);
		fracDinoCrouching->setWorldPosition(node->getWorldPosition() + Math::vec3_back * 10);
		fracDinoCrouching->setParent(node);

		mesh = checked_ptr_cast<ObjectMeshStatic>(playerProperties->mesh.get());
		auto body = mesh->getObjectBodyRigid();
		destroyCallBackID = body->addContactEnterCallback(MakeCallback(this, &DinoDestroy::destroy));
	}
}

void DinoDestroy::update()
{
}

void DinoDestroy::destroy(BodyPtr body, int num)
{
	auto animator = ComponentSystem::get()->getComponent<VoxAnimator>(mesh);
	bool isCrouching = animator->getCurrentAnimation() == "crouching";
	if (!isCrouching)
	{
		fracDino->setWorldPosition(mesh->getChild(0)->getWorldPosition());
		node->removeWorldChild(fracDino);
		fracDinoCrouching->setEnabled(false);
	}
	else
	{
		fracDinoCrouching->setWorldPosition(mesh->getChild(0)->getWorldPosition());
		node->removeWorldChild(fracDinoCrouching);
		fracDino->setEnabled(false);
	}
	node->removeWorldChild(camera);
	auto bodyy = mesh->getObjectBodyRigid();
	bodyy->removeContactEnterCallback(destroyCallBackID);
	playerProperties->mesh->setEnabled(false);
}

void DinoDestroy::shutDown()
{
	auto body = mesh->getObjectBodyRigid();
	body->removeContactEnterCallback(destroyCallBackID);
}