#pragma once
#include "ydmEngine.h"
#include"UI_Star.h"

#define LEFT_STAR_POSITION_X (138.0f)
#define STAR_POSITION_Y (84.0f)

//���̔z��
class UI_StarList :public Create::GameObject
{
public:
	UI_StarList(NAME inName);

	bool Start()override;				//������
	bool Update()override;				//�X�V
	bool Render()override;
	bool End()override;

	UI_Star * m_StarsList[3];	//���z��
};

