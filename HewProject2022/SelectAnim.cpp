#include "SelectAnim.h"

void SelectAnim::Init()
{
	/*	�Z���N�g�ړ��`���[�g���A��	*/
	::AnimationTable set_SelectTutorial;
	set_SelectTutorial.SetKind(KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_2, KIND::MOVE_2, KIND::MOVE_2, ANIMATION_FINISH);
	set_SelectTutorial.SetFrame(TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_3, ANIMATION_FINISH);
	set_SelectTutorial.SetKey(0.0f, 300.0f, 600.0f, 900.0f, 1200.0f, 1500.0f);
	AnimationTableList.insert(std::make_pair("SelectTutorial", set_SelectTutorial));

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = TUTORIAL_ANIM::ANIM_MAX;
}
