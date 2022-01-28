#include "TutorialEffectAnim.h"

void TutorialEffectAnim::Init()
{
	/*	�`���[�g���A���G�t�F�N�g	*/
	::AnimationTable set_TutorialEffect;
	set_TutorialEffect.SetKind(KIND::EFFECT, KIND::EFFECT, KIND::EFFECT, KIND::EFFECT, KIND::EFFECT, ANIMATION_FINISH);
	set_TutorialEffect.SetFrame(TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_4, TUTORIAL_ANIM::ANIM_5, ANIMATION_FINISH);
	set_TutorialEffect.m_Key = { 0.0f, 200.0f, 400.0f, 600.0f, 800.0f, 1000.0f };
	AnimationTableList.insert(std::make_pair("TutorialEffect", set_TutorialEffect));

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = TUTORIAL_ANIM::ANIM_MAX;
}
