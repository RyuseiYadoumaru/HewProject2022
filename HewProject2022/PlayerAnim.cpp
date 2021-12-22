#include "PlayerAnim.h"

void PlayerAnim::Init()
{
	// �A�j���[�V�����ݒ�	
	std::vector<int> set_LeftWalk{ LEFT, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };

	std::vector<int> set_RightWalk{ RIGHT, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };

	std::vector<int> set_DownWalk{ DOWN, ANIM_1, ANIM_2, ANIM_3, ANIM_2,ANIMATION_LOOP };

	std::vector<int> set_UpWalk{ UP, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };


	/*	�X�s�[�h�ݒ�	*/
	m_speed = 1.0f;

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = KIND_MAX;
	FrameMax = FRAME_MAX;

	/*	���A�j���[�V����	*/
	CreateAnimation("LeftWalk", set_LeftWalk);
	/*	�E�A�j���[�V����	*/
	CreateAnimation("RightWalk", set_RightWalk);
	/*	�����s�A�j���[�V����	*/
	CreateAnimation("DownWalk", set_DownWalk);
	/*	����s�A�j���[�V����	*/
	CreateAnimation("UpWalk", set_UpWalk);
}
