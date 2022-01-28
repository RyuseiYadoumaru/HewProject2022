#pragma once
#include "ydmEngine.h"

using Create::Animation;



/****	アニメーション	****/
class PlayerAnim : public Animation
{
public:
	/*	種類	*/
	enum KIND
	{
		IDLE = 0,
		WALK,
		JUMP,
		DOWN,
		MAGIC,
		PUSH,
		ROTATELOOP,
		ROTATEEND,
		HAND,
		KIND_MAX
	};

	/*	パターン	*/
	enum PLAYER_ANIM
	{
		ANIM_1 = 0,
		ANIM_2,
		ANIM_3,
		ANIM_MAX
	};


public:
	void Init() override;

};

