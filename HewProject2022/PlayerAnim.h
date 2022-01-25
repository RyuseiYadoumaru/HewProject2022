#pragma once
#include "ydmEngine.h"

using Create::Animation;



/****	�A�j���[�V����	****/
class PlayerAnim : public Animation
{
public:
	/*	���	*/
	enum KIND
	{
		IDLE,
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

	/*	�p�^�[��	*/
	enum PLAYER_ANIM
	{
		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_MAX
	};


public:
	void Init() override;

};

