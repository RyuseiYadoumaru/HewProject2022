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
		PLAYER_ONGROUND,
		PLAYER_MAGICSTART,
		PLAYER_MAGIC,
		PLAYER_EMPTY
	};

public:
	bool Init() override;
	void Update() override;
};

