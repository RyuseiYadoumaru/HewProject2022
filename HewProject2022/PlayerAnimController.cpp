#include "PlayerAnimController.h"

bool PlayerAnimController::Init()
{
	Anim = make_shared<PlayerAnim>();
	Anim->Init();
	AnimState = PLAYER_IDLE;

	return true;

}

void PlayerAnimController::Update()
{
	switch (AnimState)
	{
	case PLAYER_EMPTY:
		Anim->Play("Empty");
		break;

	case PLAYER_WALK:
		Anim->Play("Walk");
		break;

	case PLAYER_IDLE:
		Anim->Play("Idle");
		break;

	case PLAYER_DOWN:
		Anim->Play("Down");
		break;

	case PLAYER_JUMP:
		if (Anim->Play("Jump") == ANIMATION_FINISH)
		{
			AnimState = PLAYER_DOWN;
		}
		break;

	case PLAYER_ONGROUND:
		if (Anim->Play("OnGround") == ANIMATION_FINISH)
		{
			AnimState = PLAYER_EMPTY;
		}
		break;

	case PLAYER_MAGICSTART:
		if (Anim->Play("MagicStart") == ANIMATION_FINISH)
		{
			AnimState = PLAYER_MAGIC;
		}
		break;

	case PLAYER_MAGIC:
		Anim->Play("Magic");
		break;

	default:
		break;
	}

}
