#include "TutorialAnimController.h"

#include "MoveTutorial.h"

using namespace GameEngine;

bool TutorialAnimController::Init()
{
	Anim = make_shared<TutorialAnim>();
	Anim->Init();

	return true;
}

void TutorialAnimController::Update()
{
	/*Player* m_Player = Create::Scene::GetGameObject<Player>("Player");
	MoveTutorial* m_MoveTutorial = Create::Scene::GetGameObject<MoveTutorial>("MoveTutorial");*/

	Anim->Play("WalkTutorial");
}