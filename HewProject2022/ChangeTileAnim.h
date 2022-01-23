#pragma once
#include "ydmEngine.h"

using Create::Animation;

//入れ替えギミックのタイル用のアニメーション

class ChangeTileAnim :public Animation
{
public:
	/*	種類	*/
	enum KIND
	{
		//これいらんかったわ
	};

	/*	パターン	*/
	enum REPLACEMENT_TILE_ANIM
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