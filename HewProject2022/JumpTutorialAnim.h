#pragma once
#include "ydmEngine.h"

using Create::Animation;

class JumpTutorialAnim : public Animation
{
public:
	/*	���	*///�c�@�W�����v�ƕ�������ǂ���������
	enum KIND
	{
		JUMP,
		KIND_MAX
	};

	/*	�p�^�[��	*/
	enum TUTORIAL_ANIM//��
	{
		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_4,
		ANIM_5,
		ANIM_MAX
	};
public:
	void Init() override;

};

