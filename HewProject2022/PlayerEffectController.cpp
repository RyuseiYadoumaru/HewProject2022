#include "PlayerEffectController.h"
/* ゴールアニメーションコントローラークラス */
bool PlayerEffectController::Init()
{
	Anim = make_shared<PlayerEffect>();
	Anim->Init();
	AnimState = PLAYER_EMPTY;

	return true;
}

void PlayerEffectController::Update()
{
	switch (AnimState) {
	case PLAYER_EFFECT:
		Anim->Play("GoalPlayerEffect");
		break;

	case PLAYER_EMPTY:
		break;

	default:
		break;
	}
}

void PlayerEffect::Init()
{
	const float GOAL_KeyFrame = 200.0f;

	/*	GOALPLAYEREFFECT	*/
	::AnimationTable set_GoalPlayerEffect;
	set_GoalPlayerEffect.SetKind(KIND::EFFECT, KIND::EFFECT, KIND::EFFECT, KIND::EFFECT, KIND::EFFECT, KIND::EFFECT, KIND::EFFECT, KIND::EFFECT, KIND::EFFECT);
	set_GoalPlayerEffect.SetFrame(GOALPLAYER_EFFECT::ANIM_1, GOALPLAYER_EFFECT::ANIM_2, GOALPLAYER_EFFECT::ANIM_3,
		GOALPLAYER_EFFECT::ANIM_4, GOALPLAYER_EFFECT::ANIM_5, GOALPLAYER_EFFECT::ANIM_6,
		GOALPLAYER_EFFECT::ANIM_7, GOALPLAYER_EFFECT::ANIM_8, GOALPLAYER_EFFECT::ANIM_9, ANIMATION_FINISH);
	set_GoalPlayerEffect.m_Key = { GOAL_KeyFrame * 0, GOAL_KeyFrame * 1, GOAL_KeyFrame * 2,
		GOAL_KeyFrame * 3, GOAL_KeyFrame * 4, GOAL_KeyFrame * 5,
		GOAL_KeyFrame * 6, GOAL_KeyFrame * 7, GOAL_KeyFrame * 8 };
	AnimationTableList.insert(std::make_pair("GoalPlayerEffect", set_GoalPlayerEffect));

	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = GOALPLAYER_EFFECT::ANIM_MAX;
}
