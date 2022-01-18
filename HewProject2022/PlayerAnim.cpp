#include "PlayerAnim.h"

void PlayerAnim::Init()
{

	/*	Empty	*/
	::AnimationTable set_Empty;
	set_Empty.SetKind(KIND::IDLE);
	set_Empty.SetFrame(PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Empty.SetKey(0.0f);
	AnimationTableList.insert(std::make_pair("Empty", set_Empty));

	/*	待機	*/
	::AnimationTable set_Idle;
	set_Idle.SetKind(KIND::IDLE, KIND::IDLE, KIND::IDLE, ANIMATION_FINISH);
	set_Idle.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Idle.SetKey(0.0f, 1000.0f, 1250.0f);
	AnimationTableList.insert(std::make_pair("Idle", set_Idle));

	/*	歩く	*/
	::AnimationTable set_Walk;
	set_Walk.SetKind(KIND::WALK, KIND::IDLE, KIND::WALK, KIND::IDLE, KIND::WALK, ANIMATION_FINISH);
	set_Walk.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Walk.SetKey(0.0f, 350.0f, 400.0f, 750.0f, 800.0f);
	AnimationTableList.insert(std::make_pair("Walk", set_Walk));


	/*	ジャンプ	*/
	::AnimationTable set_Jump;
	set_Jump.SetKind(KIND::IDLE, KIND::JUMP, KIND::JUMP, KIND::JUMP, ANIMATION_FINISH);
	set_Jump.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, ANIMATION_FINISH);
	set_Jump.SetKey(0.0f, 10.0f, 150.0f, 250.0f);
	AnimationTableList.insert(std::make_pair("Jump", set_Jump));

	/*	落下	*/
	::AnimationTable set_Down;
	set_Down.SetKind(KIND::DOWN, KIND::DOWN);
	set_Down.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Down.SetKey(0.0f, 20.0f);
	AnimationTableList.insert(std::make_pair("Down", set_Down));

	/*	着地	*/
	::AnimationTable set_OnGround;
	set_OnGround.SetKind(KIND::DOWN, KIND::IDLE);
	set_OnGround.SetFrame(PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_OnGround.SetKey(0.0f, 130.0f);
	AnimationTableList.insert(std::make_pair("OnGround", set_OnGround));

	/*	魔法開始	*/
	::AnimationTable set_MagicStart;
	set_MagicStart.SetKind(KIND::IDLE, KIND::MAGIC, KIND::MAGIC);
	set_MagicStart.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_MagicStart.SetKey(0.0f, 100.0f, 200.0f);
	AnimationTableList.insert(std::make_pair("MagicStart", set_MagicStart));

	/*	魔法中	*/
	::AnimationTable set_Magic;
	set_Magic.SetKind(KIND::MAGIC, KIND::MAGIC, KIND::MAGIC);
	set_Magic.SetFrame(PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_Magic.SetKey(0.0f, 150.0f, 300.0f);
	AnimationTableList.insert(std::make_pair("Magic", set_Magic));


	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = PLAYER_ANIM::ANIM_MAX;

}
