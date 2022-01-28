#include "JumpTutorialAnim.h"


void JumpTutorialAnim::Init()
{
	/*  �W�����v����`���[�g���A��	*/
	::AnimationTable set_JumpTutorial;
	set_JumpTutorial.SetKind(KIND::JUMP, KIND::JUMP, KIND::JUMP, KIND::JUMP, KIND::JUMP, KIND::JUMP, ANIMATION_FINISH);
	set_JumpTutorial.SetFrame(TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_4, TUTORIAL_ANIM::ANIM_5, ANIMATION_FINISH);
	set_JumpTutorial.m_Key = { 0.0f, 1000.0f, 1150.0f, 1300.0f, 1450.0f, 1600.0f };
	AnimationTableList.insert(std::make_pair("JumpTutorial", set_JumpTutorial));

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = TUTORIAL_ANIM::ANIM_MAX;
}
