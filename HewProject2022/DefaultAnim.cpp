#include "DefaultAnim.h"

void DefaultAnim::Init()
{
	::AnimationTable s_LeftWalk;
	s_LeftWalk.SetKind(LEFT, LEFT, LEFT, LEFT, ANIMATION_LOOP);
	s_LeftWalk.SetFrame(ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP);

	::AnimationTable s_RightWalk;
	s_RightWalk.SetKind(RIGHT, RIGHT, RIGHT, RIGHT, ANIMATION_LOOP);
	s_RightWalk.SetFrame(ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP);
	::AnimationTable s_UpWalk;
	s_UpWalk.SetKind(UP, UP, UP, UP, ANIMATION_LOOP);
	s_UpWalk.SetFrame(ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP);
	::AnimationTable s_DownWalk;
	s_DownWalk.SetKind(DOWN, DOWN, DOWN, DOWN, ANIMATION_LOOP);
	s_DownWalk.SetFrame(ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP);


	//// �A�j���[�V�����ݒ�	
	//std::vector<int> set_LeftWalk{ LEFT, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };

	//std::vector<int> set_RightWalk{ RIGHT, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };

	//std::vector<int> set_DownWalk{ DOWN, ANIM_1, ANIM_2, ANIM_3, ANIM_2,ANIMATION_LOOP };

	//std::vector<int> set_UpWalk{ UP, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };


	/*	�X�s�[�h�ݒ�	*/
	m_speed = 0.25f;

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = KIND_MAX;
	FrameMax = FRAME_MAX;

	/*	���A�j���[�V����	*/
	AnimationTableList.insert(std::make_pair("LeftWalk", s_LeftWalk));
	/*	�E�A�j���[�V����	*/
	AnimationTableList.insert(std::make_pair("RightWalk", s_RightWalk));
	/*	����s�A�j���[�V����	*/
	AnimationTableList.insert(std::make_pair("UpWalk", s_UpWalk));
	/*	�����s�A�j���[�V����	*/
	AnimationTableList.insert(std::make_pair("DownWalk", s_DownWalk));
}
