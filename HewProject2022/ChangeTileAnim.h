#pragma once
#include "ydmEngine.h"

using Create::Animation;

//����ւ��M�~�b�N�̃^�C���p�̃A�j���[�V����

class ChangeTileAnim :public Animation
{
public:
	/*	���	*/
	enum KIND
	{
		//���ꂢ��񂩂�����
	};

	/*	�p�^�[��	*/
	enum REPLACEMENT_TILE_ANIM
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