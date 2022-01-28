#include "PlayerAnim.h"

void PlayerAnim::Init()
{

	/*	Empty	*/
	::AnimationTable set_Empty;
	set_Empty.SetKind(KIND::IDLE, ANIMATION_FINISH);
	set_Empty.SetFrame(PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Empty.m_Key = { 0.0f };
	AnimationTableList.insert(std::make_pair("Empty", set_Empty));

	/*	待機	*/
	::AnimationTable set_Idle;
	set_Idle.SetKind(KIND::IDLE, KIND::IDLE, KIND::IDLE, ANIMATION_FINISH);
	set_Idle.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Idle.m_Key = { 0.0f, 1000.0f, 1250.0f };
	AnimationTableList.insert(std::make_pair("Idle", set_Idle));

	/*	歩く	*/
	::AnimationTable set_Walk;
	set_Walk.SetKind(KIND::WALK, KIND::IDLE, KIND::WALK, KIND::IDLE, KIND::WALK, ANIMATION_FINISH);
	set_Walk.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Walk.m_Key = { 0.0f, 350.0f, 400.0f, 750.0f, 800.0f };
	AnimationTableList.insert(std::make_pair("Walk", set_Walk));


	/*	ジャンプ	*/
	::AnimationTable set_Jump;
	set_Jump.SetKind(KIND::IDLE, KIND::JUMP, KIND::JUMP, KIND::JUMP, ANIMATION_FINISH);
	set_Jump.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, ANIMATION_FINISH);
	set_Jump.m_Key = { 0.0f, 10.0f, 150.0f, 250.0f };
	AnimationTableList.insert(std::make_pair("Jump", set_Jump));

	/*	落下	*/
	::AnimationTable set_Down;
	set_Down.SetKind(KIND::DOWN, KIND::DOWN, ANIMATION_FINISH);
	set_Down.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Down.m_Key = { 0.0f, 20.0f };
	AnimationTableList.insert(std::make_pair("Down", set_Down));

	/*	着地	*/
	::AnimationTable set_OnGround;
	set_OnGround.SetKind(KIND::DOWN, KIND::IDLE, ANIMATION_FINISH);
	set_OnGround.SetFrame(PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_OnGround.m_Key = { 0.0f, 70.0f };
	AnimationTableList.insert(std::make_pair("OnGround", set_OnGround));

	/*	魔法開始	*/
	::AnimationTable set_MagicStart;
	set_MagicStart.SetKind(KIND::IDLE, KIND::MAGIC, KIND::MAGIC, ANIMATION_FINISH);
	set_MagicStart.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_MagicStart.m_Key = { 0.0f, 100.0f, 200.0f };
	AnimationTableList.insert(std::make_pair("MagicStart", set_MagicStart));

	/*	魔法中	*/
	::AnimationTable set_Magic;
	set_Magic.SetKind(KIND::MAGIC, KIND::MAGIC, KIND::MAGIC, ANIMATION_FINISH);
	set_Magic.SetFrame(PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_Magic.m_Key = { 0.0f, 150.0f, 300.0f };
	AnimationTableList.insert(std::make_pair("Magic", set_Magic));

	/*	PUSH	*/
	::AnimationTable set_Push;
	set_Push.SetKind(KIND::PUSH, KIND::PUSH, KIND::PUSH, ANIMATION_FINISH);
	set_Push.SetFrame(PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_Push.m_Key = { 0.0f, 150.0f, 300.0f };
	AnimationTableList.insert(std::make_pair("Push", set_Magic));

	/*	ROTATESTART	*/
	::AnimationTable set_RotateStart;
	set_RotateStart.SetKind(KIND::PUSH, KIND::ROTATELOOP, KIND::ROTATELOOP, KIND::ROTATELOOP, ANIMATION_FINISH);
	set_RotateStart.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, ANIMATION_FINISH);
	set_RotateStart.m_Key = { 0.0f, 400.0f, 700.0f, 1000.0f };
	AnimationTableList.insert(std::make_pair("RotateStart", set_RotateStart));

	/*	ROTATELOOP	*/
	::AnimationTable set_RotateLoop;
	set_RotateLoop.SetKind(KIND::ROTATELOOP, KIND::ROTATELOOP, KIND::ROTATELOOP, ANIMATION_FINISH);
	set_RotateLoop.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, ANIMATION_FINISH);
	set_RotateLoop.m_Key = { 0.0f, 300.0f, 600.0f };
	AnimationTableList.insert(std::make_pair("RotateLoop", set_RotateLoop));

	/*	ROTATEEND	*/
	::AnimationTable set_RotateEnd;
	set_RotateEnd.SetKind(KIND::ROTATELOOP, KIND::ROTATEEND, KIND::ROTATEEND, ANIMATION_FINISH);
	set_RotateEnd.SetFrame(PLAYER_ANIM::ANIM_3, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_RotateEnd.m_Key = { 0.0f, 500.0f, 1000.0f };
	AnimationTableList.insert(std::make_pair("RotateEnd", set_RotateEnd));

	/*	HAND	*/
	::AnimationTable set_Hand;
	set_Hand.SetKind(KIND::HAND, KIND::HAND, ANIMATION_FINISH);
	set_Hand.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_Hand.m_Key = { 0.0f, 500.0f };
	AnimationTableList.insert(std::make_pair("Hand", set_Hand));


	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = (int)KIND::KIND_MAX;
	FrameMax = (int)PLAYER_ANIM::ANIM_MAX;

}
