#include "Tutorial_XYAnimController.h"

bool Tutorial_XYAnimController::Init()
{
	Anim = make_shared<Tutorial_XYAnim>();
	Anim->Init();

	return true;
}

void Tutorial_XYAnimController::Update()
{
	Anim->Play("X_Tutorial");
}
