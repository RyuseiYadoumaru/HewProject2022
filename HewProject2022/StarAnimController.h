#pragma once
#include "ydmEngine.h"

/* ゴールアニメーションコントローラークラス */
class StarAnimController :public Create::AnimationController
{
public:
	enum
	{
		NONE,
		STAR_1,
		STAR_2,
		STAR_3,
		STAR_1END,
		STAR_2END,
		STAR_3END
	};

public:
	bool Init() override;
	void Update() override;
};


/* ゴールアニメーションクラス */
class StarAnim :public Create::Animation {
public:
	/*	種類	*/
	enum KIND
	{
		ANIMATION_1,
		ANIMATION_2,
		ANIMATION_3,
		ANIMATION_4,
		KIND_MAX
	};

	/*	パターン	*/
	enum STAR_ANIM
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
		ANIM_MAX
	};
	//4*10のアニメーション

public:
	void Init() override;
};

