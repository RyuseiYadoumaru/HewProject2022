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

	default:
		break;
	}

}
