#pragma once
#include "ydmEngine.h"
#include "TutorialAnim.h"
//����͈ړ��̃`���[�g���A���p�ł�

class TutorialAnimController :public Create::AnimationController
{

public:
	bool Init() override;
	void Update() override;
};

