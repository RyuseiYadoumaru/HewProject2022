#include "SelectAnimController.h"
#include "SelectTutorial.h"
#include "SelectAnim.h"

bool SelectAnimController::Init()
{
	Anim = make_shared<SelectAnim>();
	Anim->Init();

	return true;
}

void SelectAnimController::Update()
{
	Anim->Play("SelectTutorial");
}
