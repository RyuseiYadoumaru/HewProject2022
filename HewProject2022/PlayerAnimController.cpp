#include "PlayerAnimController.h"

bool PlayerAnimController::Init()
{
	Anim = make_shared<PlayerAnim>();
	Anim->Init();
	AnimState = PLAYER_IDLE;
	flg = 0;

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

	case PLAYER_PUSH:
		Anim->Play("Push");
		break;

	case PLAYER_ROTATESTART:
		Anim->Play("RotateStart");
		if (Anim->Play("RotateStart") == ANIMATION_FINISH) {
			AnimState = PLAYER_ROTATELOOP;
		}
		break;

	case PLAYER_ROTATELOOP:

		Anim->Play("RotateLoop");
		if (Anim->Play("RotateLoop") == ANIMATION_FINISH || flg == 1)
		{
			AnimState = PLAYER_ROTATEEND;
		}
		else if (Anim->Play("RotateLoop") == ANIMATION_FINISH) {
			flg = 1;
		}
		break;

	case PLAYER_ROTATEEND:
		Anim->Play("RotateEnd");
		if (Anim->Play("RotateEnd") == ANIMATION_FINISH)
		{
			AnimState = PLAYER_HAND;
		}
		break;

	case PLAYER_HAND:
		Anim->Play("Hand");
		if (Anim->Play("Hand") == ANIMATION_FINISH)
		{
			AnimState = PLAYER_HANDLOOP;
		}

		break;

	case PLAYER_HANDLOOP:
		Anim->Play("Hand");

		if (Anim->Play("Hand") == ANIMATION_FINISH || flg == 2)
		{
			AnimState = PLAYER_ANIMEND;
		}
		else if (Anim->Play("Hand") == ANIMATION_FINISH)
		{
			flg = 2;
		}
		break;
	case PLAYER_ANIMEND:
		//Anim->Play("Hand");
		break;

	default:
		break;
	}
}
