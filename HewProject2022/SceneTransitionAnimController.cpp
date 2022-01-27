#include "SceneTransitionAnimController.h"

bool SceneTransitionAnimController::Init()
{
	Anim = make_shared<SceneTransitionAnim>();
	Anim->Init();
	AnimState = SCENE_LIGHT_OFF;

	return true;
}

void SceneTransitionAnimController::Update()
{
	switch (AnimState)
	{
	case SCENE_ANIM_STOP:
		//‚±‚±‚Å‚Í‰½‚à‚µ‚È‚¢
		break;

	case SCENE_LIGHT_OFF:
		if (Anim->Play("LightOff") == ANIMATION_FINISH) {
			AnimState = SCENE_NOISE_OFF;
		}
		break;

	case SCENE_NOISE_OFF:

		Anim->Play("NoiseOff");

		break;

	default:
		break;
	}
}
