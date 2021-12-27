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
		IDLE,
		WALK,
		JUMP,
		DOWN,
		KIND_MAX
	};

	/*	パターン	*/
	enum FRAME
	{
		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_4,

		ANIM_MAX
	};


public:
	void Init() override;

};

