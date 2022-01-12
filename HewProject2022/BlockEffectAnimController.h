#pragma once
#include "ydmEngine.h"

enum
{
	EFFECT_END,
	EFFECT_STOP,
	EFFECT_PLAY
};
/****	ブロックアニメーションコントローラ	****/
class BlockMagicAnimController : public Create::AnimationController
{
public:

public:
	bool Init() override;
	void Update() override;

};

class BlockMoveAnimController : public Create::AnimationController
{
public:

public:
	bool Init() override;
	void Update() override;

};
class BlockResetAnimController : public Create::AnimationController
{
public:

public:
	bool Init() override;
	void Update() override;

};
