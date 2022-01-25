#pragma once
#include "ydmEngine.h"

/* ゴールアニメーションコントローラークラス */
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


/* ゴールアニメーションクラス */
class GoalAnim :public Create::Animation {
public:
	/*	種類	*/
	enum KIND
	{
		EFFECT_1,
		EFFECT_2,
		EFFECT_3,
		KIND_MAX
	};

	/*	パターン	*/
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

