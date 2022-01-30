#pragma once
#include "ydmEngine.h"

/* ゴールアニメーションコントローラークラス */
class FireworkController :public Create::AnimationController
{
public:
	enum
	{
		NONE,
		EFFECT_S
	};

public:
	bool Init() override;
	void Update() override;
};


/* ゴールアニメーションクラス */
class FireworkAnim :public Create::Animation {
public:
	/*	種類	*/
	enum KIND
	{
		ANIMATION_1,
		ANIMATION_2,
		KIND_MAX
	};

	/*	パターン	*/
	enum FIREWORK_ANIM
	{
		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_4,
		ANIM_5,
		ANIM_6,
		ANIM_7,
		ANIM_8,
		ANIM_9,
		ANIM_10,
		ANIM_11,
		ANIM_12,
		ANIM_13,
		ANIM_14,
		ANIM_15,
		ANIM_16,
		ANIM_17,
		ANIM_18,
		ANIM_19,
		ANIM_20,
		ANIM_21,
		ANIM_22,
		ANIM_23,
		ANIM_24,
		ANIM_25,
		ANIM_MAX
	};


public:
	void Init() override;
};

