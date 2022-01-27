#pragma once
#include "ydmEngine.h"
#include "PlayerAnim.h"
class PlayerAnimController : public Create::AnimationController
{
public:
	bool flg = 0;
	enum
	{
		PLAYER_WALK,
		PLAYER_IDLE,
		PLAYER_JUMP,
		PLAYER_DOWN,
		PLAYER_ONGROUND,
		PLAYER_MAGICSTART,
		PLAYER_MAGIC,
		PLAYER_PUSH,
		PLAYER_ROTATESTART,
		PLAYER_ROTATELOOP,
		PLAYER_ROTATEEND,
		PLAYER_HAND,
		PLAYER_HANDLOOP,
		PLAYER_ANIMEND,
		PLAYER_EMPTY
	};

public:
	bool Init() override;
	void Update() override;
};

