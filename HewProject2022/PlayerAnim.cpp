#include "PlayerAnim.h"

void PlayerAnim::Init()
{

	/*	�ҋ@	*/
	::AnimationTable set_Idle;
	set_Idle.SetKind(KIND::IDLE, KIND::IDLE, ANIMATION_FINISH);
	set_Idle.SetFrame(FRAME::ANIM_1, FRAME::ANIM_1, ANIMATION_FINISH);
	set_Idle.SetKey(0.0f, 1.0f);
	AnimationTableList.insert(std::make_pair("Idle", set_Idle));

	/*	����	*/
	::AnimationTable set_Walk;
	set_Walk.SetKind(KIND::WALK, KIND::WALK, KIND::WALK, ANIMATION_FINISH);
	set_Walk.SetFrame(FRAME::ANIM_1, FRAME::ANIM_2, FRAME::ANIM_1, ANIMATION_FINISH);
	set_Walk.SetKey(0.0f, 1000.0f, 2000.0f);
	AnimationTableList.insert(std::make_pair("Walk", set_Walk));


	/*	�W�����v	*/
	::AnimationTable set_Jump;
	set_Jump.SetKind(KIND::JUMP, KIND::JUMP, KIND::JUMP, KIND::DOWN, KIND::DOWN, ANIMATION_FINISH);
	set_Jump.SetFrame(FRAME::ANIM_1, FRAME::ANIM_2, FRAME::ANIM_3, FRAME::ANIM_1, FRAME::ANIM_2, ANIMATION_FINISH);
	set_Jump.SetKey(0.0f, 200.0f, 400.0f, 600.0f, 800.0f);
	AnimationTableList.insert(std::make_pair("Jump", set_Jump));

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = FRAME::ANIM_MAX;

}
