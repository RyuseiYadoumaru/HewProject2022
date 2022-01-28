#pragma once
#include "ydmEngine.h"

using Create::Animation;
class PlayerEffectController : public Create::AnimationController
{
public:
	enum
	{
		PLAYER_EFFECT,
		PLAYER_EMPTY
	};

public:
	bool Init() override;
	void Update() override;
};

class PlayerEffect : public Animation
{
public:
	/*	éÌóﬁ	*/
	enum KIND
	{
		EFFECT,
		KIND_MAX
	};

	/*	ÉpÉ^Å[Éì	*/
	enum GOALPLAYER_EFFECT {

		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_4,
		ANIM_5,
		ANIM_6,
		ANIM_7,
		ANIM_8,
		ANIM_9,
		ANIM_MAX
	};


public:
	void Init() override;

};