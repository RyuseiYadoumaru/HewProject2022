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

		////‰½‚à‚µ‚È‚¢NB‚Ìê‡
		//NB,

		////F‚ª•Ï‚í‚é’iŠK
		///*RED_BLUE,
		//BLUE_GREEN,
		//GREEN_PURPLE,
		//PURPLE_RED,*/

		////F‚ª•Ï‚í‚Á‚½Œã
		//RED_BLUE,
		//BLUE_GREEN,
		//GREEN_PURPLE,
		//PURPLE_RED,
	};

public:
	bool Init() override;
	void Update() override;
};
