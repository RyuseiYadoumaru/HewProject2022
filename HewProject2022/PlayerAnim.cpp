#include "PlayerAnim.h"

void PlayerAnim::Init()
{
	// �A�j���[�V�����ݒ�	
	int set_LeftWalk[] = { LEFT, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };

	int set_RightWalk[] = { RIGHT, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };

	int set_DownWalk[] = { DOWN, ANIM_1, ANIM_2, ANIM_3, ANIM_2,ANIMATION_LOOP };

	int set_UpWalk[] = { UP, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };


	/*	�X�s�[�h�ݒ�	*/
	m_speed = 1.0f;

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	���A�j���[�V����	*/
	left_walk.assign(&set_LeftWalk[0], &set_LeftWalk[sizeof(set_LeftWalk) / sizeof(int)]);

	/*	�E�A�j���[�V����	*/
	right_walk.assign(&set_RightWalk[0], &set_RightWalk[sizeof(set_RightWalk) / sizeof(int)]);

	/*	�����s�A�j���[�V����	*/
	down_walk.assign(&set_DownWalk[0], &set_DownWalk[sizeof(set_DownWalk) / sizeof(int)]);

	/*	����s�A�j���[�V����	*/
	up_walk.assign(&set_UpWalk[0], &set_UpWalk[sizeof(set_UpWalk) / sizeof(int)]);

}
