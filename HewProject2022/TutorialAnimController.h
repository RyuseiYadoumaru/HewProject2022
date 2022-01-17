#pragma once
#include "ydmEngine.h"
#include "TutorialAnim.h"
//これは移動のチュートリアル用です

class TutorialAnimController :public Create::AnimationController
{

public:
	bool Init() override;
	void Update() override;
};

