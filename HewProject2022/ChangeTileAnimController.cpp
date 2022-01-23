#include "ChangeTileAnimController.h"
#include"Tile.h"
#include "Map.h"

bool ChangeTileAnimController::Init()
{
	Anim = make_shared<ChangeTileAnim>();
	Anim->Init();
	AnimState = EMPTY;//初期は何もしない

	return true;
}

void ChangeTileAnimController::Update()
{
	//Tile一つずつが持っているので、ここで全探索する意味はないのでは！？ 01/19
	switch (AnimState)
	{
	case EMPTY:
		//NBだったら何もしない処理
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
