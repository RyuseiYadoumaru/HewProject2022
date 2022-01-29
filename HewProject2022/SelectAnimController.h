#pragma once
#include "ydmEngine.h"
#include "SelectAnim.h"

class SelectAnimController :public Create::AnimationController
{
public:
	enum
	{
		IDLE,
		RIGHT,
		LEFT,
		RIGHT_END,
		LEFT_END
	};

public:
	bool Init() override;
	void Update() override;
};