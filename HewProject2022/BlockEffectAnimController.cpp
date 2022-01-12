#include "BlockEffectAnimController.h"
#include "BlockEffect.h"
bool BlockMagicAnimController::Init()
{
	Anim = make_shared<BlockMagicAnim>();
	Anim->Init();
	AnimState = EFFECT_PLAY;
	return true;
}
void BlockMagicAnimController::Update()
{
	switch (AnimState)
	{
	case EFFECT_END:
		Anim->Delete();
		break;

	case EFFECT_STOP:
		Anim->Stop();

		break;

	case EFFECT_PLAY:
		Anim->Play("Effect");
		break;
	}
}



bool BlockMoveAnimController::Init()
{
	Anim = make_shared<BlockMoveAnim>();
	Anim->Init();
	AnimState = EFFECT_PLAY;
	return true;
}
void BlockMoveAnimController::Update()
{
	switch (AnimState)
	{
	case EFFECT_END:
		Anim->Delete();
		break;

	case EFFECT_STOP:
		Anim->Stop();
		break;

	case EFFECT_PLAY:
		Anim->Play("Effect");
		break;
	}
}



bool BlockResetAnimController::Init()
{
	Anim = make_shared<BlockResetAnim>();
	Anim->Init();
	AnimState = EFFECT_PLAY;
	return true;
}

void BlockResetAnimController::Update()
{
	switch (AnimState)
	{
	case EFFECT_END:
		Anim->Delete();
		break;

	case EFFECT_STOP:
		Anim->Stop();
		break;

	case EFFECT_PLAY:
		Anim->Play("Effect");
		break;
	}
}
