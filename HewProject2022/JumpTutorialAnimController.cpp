#include "JumpTutorialAnimController.h"

bool JumpTutorialAnimController::Init()
{
	Anim = make_shared<JumpTutorialAnim>();
	Anim->Init();

	return true;
}

void JumpTutorialAnimController::Update()
{
	Anim->Play("JumpTutorial");
}
