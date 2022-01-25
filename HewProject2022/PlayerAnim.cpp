#include "PlayerAnim.h"

void PlayerAnim::Init()
{

	/*	Empty	*/
	::AnimationTable set_Empty;
	set_Empty.SetKind(KIND::IDLE);
	set_Empty.SetFrame(PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Empty.SetKey(0.0f);
	AnimationTableList.insert(std::make_pair("Empty", set_Empty));

	/*	�ҋ@	*/
	::AnimationTable set_Idle;
	set_Idle.SetKind(KIND::IDLE, KIND::IDLE, KIND::IDLE, ANIMATION_FINISH);
	set_Idle.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Idle.SetKey(0.0f, 1000.0f, 1250.0f);
	AnimationTableList.insert(std::make_pair("Idle", set_Idle));

	/*	����	*/
	::AnimationTable set_Walk;
	set_Walk.SetKind(KIND::WALK, KIND::IDLE, KIND::WALK, KIND::IDLE, KIND::WALK, ANIMATION_FINISH);
	set_Walk.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Walk.SetKey(0.0f, 350.0f, 400.0f, 750.0f, 800.0f);
	AnimationTableList.insert(std::make_pair("Walk", set_Walk));


	/*	�W�����v	*/
	::AnimationTable set_Jump;
	set_Jump.SetKind(KIND::IDLE, KIND::JUMP, KIND::JUMP, KIND::JUMP, ANIMATION_FINISH);
	set_Jump.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, ANIMATION_FINISH);
	set_Jump.SetKey(0.0f, 10.0f, 150.0f, 250.0f);
	AnimationTableList.insert(std::make_pair("Jump", set_Jump));

	/*	����	*/
	::AnimationTable set_Down;
	set_Down.SetKind(KIND::DOWN, KIND::DOWN);
	set_Down.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Down.SetKey(0.0f, 20.0f);
	AnimationTableList.insert(std::make_pair("Down", set_Down));

	/*	���n	*/
	::AnimationTable set_OnGround;
	set_OnGround.SetKind(KIND::DOWN, KIND::IDLE);
	set_OnGround.SetFrame(PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_1, ANIMATION_FINISH);
	set_OnGround.SetKey(0.0f, 130.0f);
	AnimationTableList.insert(std::make_pair("OnGround", set_OnGround));

	/*	���@�J�n	*/
	::AnimationTable set_MagicStart;
	set_MagicStart.SetKind(KIND::IDLE, KIND::MAGIC, KIND::MAGIC);
	set_MagicStart.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_MagicStart.SetKey(0.0f, 100.0f, 200.0f);
	AnimationTableList.insert(std::make_pair("MagicStart", set_MagicStart));

	/*	���@��	*/
	::AnimationTable set_Magic;
	set_Magic.SetKind(KIND::MAGIC, KIND::MAGIC, KIND::MAGIC);
	set_Magic.SetFrame(PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_Magic.SetKey(0.0f, 150.0f, 300.0f);
	AnimationTableList.insert(std::make_pair("Magic", set_Magic));

	/*	PUSH	*/
	::AnimationTable set_Push;
	set_Push.SetKind(KIND::PUSH, KIND::PUSH, KIND::PUSH);
	set_Push.SetFrame(PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_Push.SetKey(0.0f, 150.0f, 300.0f);
	AnimationTableList.insert(std::make_pair("Push", set_Magic));

	/*	ROTATESTART	*/
	::AnimationTable set_RotateStart;
	set_RotateStart.SetKind(KIND::PUSH, KIND::ROTATELOOP, KIND::ROTATELOOP, KIND::ROTATELOOP);
	set_RotateStart.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, ANIMATION_FINISH);
	set_RotateStart.SetKey(0.0f, 400.0f, 600.0f, 800.0f);
	AnimationTableList.insert(std::make_pair("RotateStart", set_RotateStart));

	/*	ROTATELOOP	*/
	::AnimationTable set_RotateLoop;
	set_RotateLoop.SetKind(KIND::ROTATELOOP, KIND::ROTATELOOP, KIND::ROTATELOOP);
	set_RotateLoop.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, PLAYER_ANIM::ANIM_3, ANIMATION_FINISH);
	set_RotateLoop.SetKey(0.0f, 200.0f, 400.0f);
	AnimationTableList.insert(std::make_pair("RotateLoop", set_RotateLoop));

	/*	ROTATEEND	*/
	::AnimationTable set_RotateEnd;
	set_RotateEnd.SetKind(KIND::ROTATELOOP, KIND::ROTATEEND, KIND::ROTATEEND);
	set_RotateEnd.SetFrame(PLAYER_ANIM::ANIM_3, PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_RotateEnd.SetKey(0.0f, 500.0f, 1000.0f);
	AnimationTableList.insert(std::make_pair("RotateEnd", set_RotateEnd));

	/*	HAND	*/
	::AnimationTable set_Hand;
	set_Hand.SetKind(KIND::HAND, KIND::HAND);
	set_Hand.SetFrame(PLAYER_ANIM::ANIM_1, PLAYER_ANIM::ANIM_2, ANIMATION_FINISH);
	set_Hand.SetKey(0.0f, 500.0f);
	AnimationTableList.insert(std::make_pair("Hand", set_Hand));


	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = PLAYER_ANIM::ANIM_MAX;

}
