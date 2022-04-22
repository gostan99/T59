#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineMap.h>
#include <UnigineVector.h>

class VoxAnimator :public Unigine::ComponentBase
{
private:
	struct Frame
	{
		int fromSurface;
		int toSurface;
	};
public:
	COMPONENT_DEFINE(VoxAnimator, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	void playAnimation(Unigine::String animation);
	Unigine::String getCurrentAnimation()const;
public:
protected:
	void init();
	void update();
private:
	void increaseFrameBy(int num);
private:
	Unigine::Map<Unigine::String, Unigine::Vector<Frame>> animations;
	PROP_PARAM(Float, fps, 12);
	PROP_PARAM(String, currentAnimation);
	Unigine::String newAnimation;
	int currentFrame = 0;
	float frequency;
	float timeElapsed = 0.f;
	bool isPaused = false;
	Unigine::ObjectMeshStaticPtr mesh;
};
