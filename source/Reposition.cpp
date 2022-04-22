#include "Reposition.h"

REGISTER_COMPONENT(Reposition)

using namespace Unigine;

float zOrigine;
void Reposition::init()
{
	zOrigine = node->getWorldPosition().z;
	trigger = checked_ptr_cast<WorldTrigger>(node);
	if (trigger)
		trigger->addEnterCallback(MakeCallback(this, &Reposition::enterCallback));
}

void Reposition::update()
{
	node->renderVisualizer();
}

void Reposition::enterCallback(Unigine::NodePtr target)
{
	node->getParent()->worldTranslate(node->getWorldDirection(Math::AXIS::AXIS_Y) * teleportDistance);
	if (node->getWorldPosition().z < zOrigine)
	{
		node->getParent()->worldTranslate(Math::vec3_up * zOrigine);
	}
}