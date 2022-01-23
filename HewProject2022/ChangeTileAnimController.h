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

		////何もしないNBの場合
		//NB,

		////色が変わる段階
		///*RED_BLUE,
		//BLUE_GREEN,
		//GREEN_PURPLE,
		//PURPLE_RED,*/

		////色が変わった後
		//RED_BLUE,
		//BLUE_GREEN,
		//GREEN_PURPLE,
		//PURPLE_RED,
	};

public:
	bool Init() override;
	void Update() override;
};
