#include "PlayerAnim.h"

void PlayerAnim::Init()
{

	/*	�ҋ@	*/
	::AnimationTable set_Idle;
	set_Idle.SetKind(KIND::IDLE, KIND::IDLE, KIND::IDLE, KIND::IDLE, ANIMATION_LOOP);
	set_Idle.SetFrame(FRAME::ANIM_1, FRAME::ANIM_1, FRAME::ANIM_1, FRAME::ANIM_1, ANIMATION_LOOP);
	AnimationTableList.insert(std::make_pair("Idle", set_Idle));

	/*	����	*/
	::AnimationTable set_Walk;
	set_Walk.SetKind(KIND::WALK, KIND::WALK, KIND::WALK, KIND::WALK, ANIMATION_LOOP);
	set_Walk.SetFrame(FRAME::ANIM_1, FRAME::ANIM_1, FRAME::ANIM_2, FRAME::ANIM_2, ANIMATION_LOOP);
	AnimationTableList.insert(std::make_pair("Walk", set_Walk));


	/*	�W�����v	*/
	::AnimationTable set_Jump;
	set_Jump.SetKind(KIND::JUMP, KIND::JUMP, KIND::JUMP, KIND::JUMP, KIND::DOWN, KIND::DOWN, ANIMATION_LOOP);
	set_Jump.SetFrame(FRAME::ANIM_1, FRAME::ANIM_1, FRAME::ANIM_2, FRAME::ANIM_3, FRAME::ANIM_1, FRAME::ANIM_2, ANIMATION_LOOP);
	AnimationTableList.insert(std::make_pair("Jump", set_Jump));

	/*	�X�s�[�h�ݒ�	*/
	m_speed = 0.15f;

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = FRAME::ANIM_MAX;

}
