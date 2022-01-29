#pragma once
#include "ydmEngine.h"

using Create::Animation;

class Tutorial_XYAnim :public Animation
{
public:
	enum KIND
	{
		X,
		KIND_MAX
	};

	enum X_TUTORIAL_ANIM//‰¡
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

