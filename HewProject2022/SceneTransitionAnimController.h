#pragma once
#include "ydmEngine.h"
#include "SceneTransitionAnim.h"

class SceneTransitionAnimController :public Create::AnimationController
{
public:
	enum
	{
		SCENE_ANIM_STOP,
		SCENE_LIGHT_OFF,
		SCENE_NOISE_OFF,
	};

public:
	bool Init() override;
	void Update() override;
};

