#include "SelectAnimController.h"
#include "SelectTutorial.h"
#include "SelectAnim.h"

bool SelectAnimController::Init()
{
	Anim = make_shared<SelectAnim>();
	Anim->Init();
	AnimState = IDLE;
	return true;
}

void SelectAnimController::Update()
{
	switch (AnimState)
	{
	case IDLE:
		Anim->Play("SelectTutorial_Idle");
		std::cout << "debug" << std::endl;
		break;

	case RIGHT:
		if (Anim->Play("SelectTutorial_Right") == ANIMATION_FINISH) {
			AnimState = RIGHT_END;
		}
		break;

	case RIGHT_END:
		Anim->Play("SelectTutorial_Right_End");
		break;

	case LEFT:
		if (Anim->Play("SelectTutorial_Left") == ANIMATION_FINISH) {
			AnimState = LEFT_END;
		}
		break;

	case LEFT_END:
		Anim->Play("SelectTutorial_Left_End");
		break;

	default:
		break;
	}
}
