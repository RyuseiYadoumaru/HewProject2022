#include "Tutorial_XYAnim.h"


void Tutorial_XYAnim::Init()
{
	/*	������`���[�g���A��	*/
	::AnimationTable set_XY_Tutorial;
	set_XY_Tutorial.SetKind(KIND::X, KIND::X, KIND::X, KIND::X, KIND::X, KIND::X, KIND::X, ANIMATION_FINISH);
	set_XY_Tutorial.SetFrame(X_TUTORIAL_ANIM::ANIM_1, X_TUTORIAL_ANIM::ANIM_2, X_TUTORIAL_ANIM::ANIM_3, X_TUTORIAL_ANIM::ANIM_4, X_TUTORIAL_ANIM::ANIM_5, X_TUTORIAL_ANIM::ANIM_6, X_TUTORIAL_ANIM::ANIM_7, ANIMATION_FINISH);
	set_XY_Tutorial.m_Key = { 0.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 600.0f };
	AnimationTableList.insert(std::make_pair("X_Tutorial", set_XY_Tutorial));

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = X_TUTORIAL_ANIM::ANIM_MAX;
}
