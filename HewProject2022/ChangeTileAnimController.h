#pragma once
#include "ydmEngine.h"
#include"ChangeTileAnim.h"

class ChangeTileAnimController : public Create::AnimationController
{
public:
	enum
	{
		EMPTY,
		CHANGE,

		////�������Ȃ�NB�̏ꍇ
		//NB,

		////�F���ς��i�K
		///*RED_BLUE,
		//BLUE_GREEN,
		//GREEN_PURPLE,
		//PURPLE_RED,*/

		////�F���ς������
		//RED_BLUE,
		//BLUE_GREEN,
		//GREEN_PURPLE,
		//PURPLE_RED,
	};

public:
	bool Init() override;
	void Update() override;
};
