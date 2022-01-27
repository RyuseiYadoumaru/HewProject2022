#pragma once
#include "ydmEngine.h"

using Create::Animation;

class SceneTransitionAnim : public Animation
{
public:
	/*	éÌóﬁ	*/
	enum KIND
	{
		LIGHT_OFF,
		NOISE_OFF,
		KIND_MAX
	};

	/*	ÉpÉ^Å[Éì	*/
	enum SCENE_ANIM
	{
		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_4,
		ANIM_5,
		ANIM_6,
		ANIM_7,
		ANIM_MAX
	};

public:
	void Init() override;

};

