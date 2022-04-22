#include "VoxAnimator.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(VoxAnimator)
using namespace Unigine;

void VoxAnimator::init()
{
	frequency = 1 / fps;

	if (node)
	{
		mesh = checked_ptr_cast<ObjectMeshStatic>(node);
		if (mesh)
		{
			// get number of material per frame and disable all surfaces
			int numMat = 1;
			String firstFrame = String::split(mesh->getSurfaceName(0), " ")[0];
			int i = 1;
			mesh->setEnabled(false, 0);
			while (i < mesh->getNumSurfaces())
			{
				mesh->setEnabled(false, i);
				if (firstFrame == String::split(mesh->getSurfaceName(i), " ")[0])
				{
					++numMat;
				}
				++i;
			}

			// Generate animations
			String animName = mesh->getSurfaceName(0);
			animName = animName.substr(0, animName.rfind("_"));
			animations.append(animName, Vector<Frame>());
			for (int i = 0; i < mesh->getNumSurfaces(); i += numMat)
			{
				mesh->setEnabled(false, i);
				String surfaceName = mesh->getSurfaceName(i);
				if (animName == surfaceName.substr(0, surfaceName.rfind("_")))
				{
					animations[animName].append(Frame{ i, i + numMat - 1 });
				}
				else
				{
					animName = surfaceName.substr(0, surfaceName.rfind("_"));
					animations.append(animName, Vector<Frame>());
					animations[animName].append(Frame{ i, i + numMat - 1 });
				}
			}

			if (String(currentAnimation.get()).empty())
			{
				currentAnimation = animName;
			}
		}
		else
		{
			Log::error("VoxAnimator component: %s is not a ObjectMeshStatic!", node->getName());
		}
	}
}

void VoxAnimator::update()
{
	if (!isPaused)
	{
		timeElapsed += Game::getIFps();
		int frameInscrease = timeElapsed / frequency;
		if (frameInscrease != 0)
		{
			increaseFrameBy(frameInscrease);
			timeElapsed = 0.f;
		}
	}
}

void VoxAnimator::increaseFrameBy(int num)
{
	int fromSurface = animations[currentAnimation.get()][currentFrame].fromSurface;
	int toSurface = animations[currentAnimation.get()][currentFrame].toSurface;
	for (size_t i = fromSurface; i <= toSurface; i++)
	{
		if (mesh)
		{
			mesh->setEnabled(false, i);
		}
	}

	if (!newAnimation.empty() && newAnimation != currentAnimation)
	{
		currentAnimation = newAnimation;
		currentFrame = 0;
		num = 0;
	}
	currentFrame = (currentFrame + num) % animations[currentAnimation.get()].size();
	fromSurface = animations[currentAnimation.get()][currentFrame].fromSurface;
	toSurface = animations[currentAnimation.get()][currentFrame].toSurface;
	for (size_t i = fromSurface; i <= toSurface; i++)
	{
		if (mesh)
		{
			mesh->setEnabled(true, i);
		}
	}
}

void VoxAnimator::playAnimation(Unigine::String animation)
{
	if (animations.contains(animation) && animation != newAnimation)
	{
		newAnimation = animation;
	}
}

Unigine::String VoxAnimator::getCurrentAnimation() const
{
	return currentAnimation.get();
}