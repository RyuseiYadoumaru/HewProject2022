#pragma once
#include "ydmEngine.h"

using Create::Animation;

class SelectAnim : public Animation
{
public:
	/*	���	*///�c�@�W�����v�ƕ�������ǂ���������
	enum KIND
	{
		MOVE_1,
		MOVE_2,
		KIND_MAX
	};

	/*	�p�^�[��	*/
	enum TUTORIAL_ANIM//��
	{
		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_MAX
	};

public:
	void Init() override;

};
