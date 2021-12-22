#include "PlayerAnimController.h"

bool PlayerAnimController::Init()
{
	Anim = make_shared<PlayerAnim>();
	Anim->Init();
	AnimState = P_LEFT;

	return true;
}

void PlayerAnimController::Update()
{
	switch (AnimState)
	{
	case P_LEFT:
		Anim->Play("LeftWalk");
		break;

	case P_RIGHT:
		Anim->Play("RightWalk");
		break;

	case P_UP:
		Anim->Play("UpWalk");
		break;

	case P_DOWN:
		Anim->Play("DownWalk");
		break;

	default:
		break;
	}

}
