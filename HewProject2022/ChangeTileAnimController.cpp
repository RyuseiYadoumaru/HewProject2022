#include "ChangeTileAnimController.h"
#include"Tile.h"
#include "Map.h"

bool ChangeTileAnimController::Init()
{
	Anim = make_shared<ChangeTileAnim>();
	Anim->Init();
	AnimState = EMPTY;//�����͉������Ȃ�

	return true;
}

void ChangeTileAnimController::Update()
{
	//Tile����������Ă���̂ŁA�����őS�T������Ӗ��͂Ȃ��̂ł́I�H 01/19
	switch (AnimState)
	{
	case EMPTY:
		//NB�������牽�����Ȃ�����
		//Anim->Play("Empty");
		break;

	case CHANGE:
		if (Anim->Play("ChangeAnim") == ANIMATION_FINISH) {
			AnimState = EMPTY;
		}
		break;

	default:
		break;
	}
}
