#include "GoalAnimController.h"


/* ゴールアニメーションコントローラークラス */
bool GoalAnimController::Init()
{
	Anim = make_shared<GoalAnim>();
	Anim->Init();
	AnimState = GOAL_EFFECT;

	return true;
}
/* ゴールアニメーションコントローラークラス */
void GoalAnimController::Update()
{
	switch (AnimState) {
	case GOAL_RESET:
		Anim->Play("GoalEffect");
		if (Anim->Play("GoalEffect") == ANIMATION_FINISH) {
			AnimState = GOAL_EFFECT;
		}
		break;

	case GOAL_EFFECT:
		Anim->Play("GoalEffect");
		if (Anim->Play("GoalEffect") == ANIMATION_FINISH) {
			AnimState = GOAL_RESET;
		}
		break;

	default:
		break;
	}

}

/* ゴールアニメーションクラス */
void GoalAnim::Init()
{
	const float EF_KeyFrame = 100.0f;
	/*	ゴールエフェクト	*/
	::AnimationTable set_GoalEffect;
	set_GoalEffect.SetKind(KIND::EFFECT_1, KIND::EFFECT_1, KIND::EFFECT_1, KIND::EFFECT_1, KIND::EFFECT_1,
		KIND::EFFECT_2, KIND::EFFECT_2, KIND::EFFECT_2, KIND::EFFECT_2, KIND::EFFECT_2,
		KIND::EFFECT_3, KIND::EFFECT_3, KIND::EFFECT_3, KIND::EFFECT_3, KIND::EFFECT_3);
	set_GoalEffect.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, PLAYER_ANIM::ANIM_4, PLAYER_ANIM::ANIM_5,
		PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, PLAYER_ANIM::ANIM_4, PLAYER_ANIM::ANIM_5,
		PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, PLAYER_ANIM::ANIM_4, PLAYER_ANIM::ANIM_5, ANIMATION_FINISH);
	set_GoalEffect.SetKey(EF_KeyFrame * 0, EF_KeyFrame * 1, EF_KeyFrame * 2, EF_KeyFrame * 3, EF_KeyFrame * 4,
		EF_KeyFrame * 5, EF_KeyFrame * 6, EF_KeyFrame * 7, EF_KeyFrame * 8, EF_KeyFrame * 9,
		EF_KeyFrame * 10, EF_KeyFrame * 11, EF_KeyFrame * 12, EF_KeyFrame * 13, EF_KeyFrame * 14);
	AnimationTableList.insert(std::make_pair("GoalEffect", set_GoalEffect));

	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = PLAYER_ANIM::ANIM_MAX;
}


