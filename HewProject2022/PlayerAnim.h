#pragma once
#include "ydmEngine.h"

/* ���� */
enum KIND
{
	DOWN,  // ������
	LEFT,  // ������
	RIGHT, // �E����
	UP,    // �����

	KIND_MAX
};

/* �p�^�[�� */
enum FRAME
{
	ANIM_1, // �A�j���[�V����1
	ANIM_2, // �A�j���[�V����2
	ANIM_3, // �A�j���[�V����3

	FRAME_MAX

};

class PlayerAnim : public Create::Animation
{
public:
	void Init() override;

};

