#pragma once
#include "ydmEngine.h"

/* �S�[���A�j���[�V�����R���g���[���[�N���X */
class GoalAnimController :public Create::AnimationController
{
public:
	enum
	{
		GOAL_EFFECT,
		GOAL_RESET
	};

public:
	bool Init() override;
	void Update() override;
};


/* �S�[���A�j���[�V�����N���X */
class GoalAnim :public Create::Animation {
public:
	/*	���	*/
	enum KIND
	{
		EFFECT_1,
		EFFECT_2,
		EFFECT_3,
		KIND_MAX
	};

	/*	�p�^�[��	*/
	enum PLAYER_ANIM
	{
		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_4,
		ANIM_5,
		ANIM_MAX
	};


public:
	void Init() override;
};

