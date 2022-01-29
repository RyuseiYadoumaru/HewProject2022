#pragma once
#include "ydmEngine.h"

using Create::Animation;

class SelectAnim : public Animation
{
public:
	/*	種類	*///縦　ジャンプと分けたら良かったかも
	enum KIND
	{
		MOVE_1,
		MOVE_2,
		KIND_MAX
	};

	/*	パターン	*/
	enum TUTORIAL_ANIM//横
	{
		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_MAX
	};

public:
	void Init() override;

};
