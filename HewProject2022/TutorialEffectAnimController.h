#pragma once
#include "ydmEngine.h"
#include "TutorialEffectAnim.h"

class TutorialEffectAnimController :public Create::AnimationController
{
public:
	bool Init() override;
	void Update() override;

private:
	bool m_MoveInitFirstFlg;//�ړ���ꏉ�����t���O
	bool m_MoveInitSecondFlg;//�ړ���񏉊����t���O

	bool m_JumpInitFirstFlg;//�W�����v��ꏉ�����t���O
	bool m_JumpInitSecondFlg;//�W�����v��񏉊����t���O
};

