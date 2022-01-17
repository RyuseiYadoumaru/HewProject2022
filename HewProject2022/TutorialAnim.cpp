#include "TutorialAnim.h"

void TutorialAnim::Init()
{
	/*	歩くチュートリアル	*/
	::AnimationTable set_MoveTutorial;
	set_MoveTutorial.SetKind(KIND::WALK, KIND::WALK, KIND::WALK, KIND::WALK, KIND::WALK, KIND::WALK, ANIMATION_FINISH);
	set_MoveTutorial.SetFrame(TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_4, TUTORIAL_ANIM::ANIM_5, TUTORIAL_ANIM::ANIM_6, ANIMATION_FINISH);
	set_MoveTutorial.SetKey(0.0f, 1000.0f, 1150.0f, 1300.0f, 1450.0f, 1600.0f);
	AnimationTableList.insert(std::make_pair("WalkTutorial", set_MoveTutorial));

	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = TUTORIAL_ANIM::ANIM_MAX;
}
