#include "TutorialAnim.h"

void TutorialAnim::Init()
{
	/*	�����`���[�g���A��	*/
	::AnimationTable set_MoveTutorial;
	set_MoveTutorial.SetKind(KIND::WALK, KIND::WALK, KIND::WALK, KIND::WALK, KIND::WALK, KIND::WALK, ANIMATION_FINISH);
	set_MoveTutorial.SetFrame(TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_4, TUTORIAL_ANIM::ANIM_5, TUTORIAL_ANIM::ANIM_6, ANIMATION_FINISH);
	set_MoveTutorial.SetKey(0.0f, 1000.0f, 1150.0f, 1300.0f, 1450.0f, 1600.0f);
	AnimationTableList.insert(std::make_pair("WalkTutorial", set_MoveTutorial));

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = TUTORIAL_ANIM::ANIM_MAX;
}
