#pragma once
#include "ydmEngine.h"
#include "PlayerAnim.h"
class PlayerAnimController : public Create::AnimationController
{
public:
	enum
	{
		PLAYER_WALK,
		PLAYER_IDLE,
		PLAYER_JUMP,
		PLAYER_DOWN,
	};

public:
	bool Init() override;
	void Update() override;
};

