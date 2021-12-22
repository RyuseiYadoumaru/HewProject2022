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
enum PA
{
	ANIM_1, // �A�j���[�V����1
	ANIM_2, // �A�j���[�V����2
	ANIM_3, // �A�j���[�V����3

	PA_MAX

};

class PlayerAnim : public Create::Animation
{
public:
	void Init() override;

	vector<int> left_walk;  // �����s�A�j���[�V���� 
	vector<int> right_walk; // �E���s�A�j���[�V����
	vector<int> down_walk;  // �����s�A�j���[�V����
	vector<int> up_walk;    // ����s�A�j���[�V����

};

