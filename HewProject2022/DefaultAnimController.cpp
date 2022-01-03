#include "DefaultAnimController.h"

bool DefaultAnimController::Init()
{
	Anim = make_shared<DefaultAnim>();
	Anim->Init();
	AnimState = P_LEFT;

	return true;
}

void DefaultAnimController::Update()
{
	switch (AnimState)
	{
	case P_LEFT:
		Anim->PlayLoop("LeftWalk");
		break;

	case P_RIGHT:
		Anim->PlayLoop("RightWalk");
		break;

	case P_UP:
		Anim->PlayLoop("UpWalk");
		break;

	case P_DOWN:
		Anim->PlayLoop("DownWalk");
		break;

	default:
		break;
	}

}
