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
		KIND_MAX
	};

	/*	�p�^�[��	*/
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

