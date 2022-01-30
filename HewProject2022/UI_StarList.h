#pragma once
#include "ydmEngine.h"
#include"UI_Star.h"

#define LEFT_STAR_POSITION_X (138.0f)
#define STAR_POSITION_Y (84.0f)

//星の配列
class UI_StarList :public Create::GameObject
{
public:
	UI_StarList(NAME inName);

	bool Start()override;				//初期化
	bool Update()override;				//更新
	bool Render()override;
	bool End()override;

	UI_Star * m_StarsList[3];	//星配列
};

