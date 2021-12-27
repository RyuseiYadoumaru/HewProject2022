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
		break;

	case PLAYER_JUMP:
		Anim->Play("Jump");
		break;

	default:
		break;
	}

}
