#include "PlayerAnim.h"

void PlayerAnim::Init()
{

	/*	Empty	*/
	::AnimationTable set_Empty;
	set_Empty.SetKind(KIND::IDLE);
	set_Empty.SetFrame(FRAME::ANIM_1, ANIMATION_FINISH);
	set_Empty.SetKey(0.0f);
	AnimationTableList.insert(std::make_pair("Empty", set_Empty));

	/*	待機	*/
	::AnimationTable set_Idle;
	set_Idle.SetKind(KIND::IDLE, KIND::IDLE, KIND::IDLE, ANIMATION_FINISH);
	set_Idle.SetFrame(FRAME::ANIM_1, FRAME::ANIM_2, FRAME::ANIM_1, ANIMATION_FINISH);
	set_Idle.SetKey(0.0f, 1000.0f, 1250.0f);
	AnimationTableList.insert(std::make_pair("Idle", set_Idle));

	/*	歩く	*/
	::AnimationTable set_Walk;
	set_Walk.SetKind(KIND::WALK, KIND::WALK, KIND::WALK, ANIMATION_FINISH);
	set_Walk.SetFrame(FRAME::ANIM_1, FRAME::ANIM_2, FRAME::ANIM_1, ANIMATION_FINISH);
	set_Walk.SetKey(0.0f, 750.0f, 1500.0f);
	AnimationTableList.insert(std::make_pair("Walk", set_Walk));


	/*	ジャンプ	*/
	::AnimationTable set_Jump;
	set_Jump.SetKind(KIND::IDLE, KIND::JUMP, KIND::JUMP, KIND::JUMP, ANIMATION_FINISH);
	set_Jump.SetFrame(FRAME::ANIM_1, FRAME::ANIM_1, FRAME::ANIM_2, FRAME::ANIM_3, ANIMATION_FINISH);
	set_Jump.SetKey(0.0f, 100.0f, 550.0f, 700.0f);
	AnimationTableList.insert(std::make_pair("Jump", set_Jump));

	/*	落下	*/
	::AnimationTable set_Down;
	set_Down.SetKind(KIND::DOWN, KIND::DOWN);
	set_Down.SetFrame(FRAME::ANIM_1, FRAME::ANIM_1, ANIMATION_FINISH);
	set_Down.SetKey(0.0f, 20.0f);
	AnimationTableList.insert(std::make_pair("Down", set_Down));

	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = FRAME::ANIM_MAX;

}
