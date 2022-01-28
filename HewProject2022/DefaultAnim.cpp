#include "DefaultAnim.h"

void DefaultAnim::Init()
{
	::AnimationTable s_LeftWalk;
	s_LeftWalk.SetKind(LEFT, LEFT, LEFT, LEFT, ANIMATION_FINISH);
	s_LeftWalk.SetFrame(ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_FINISH);
	s_LeftWalk.m_Key = { 0.0f, 100.0f, 200.0f, 300.0f };

	::AnimationTable s_RightWalk;
	s_RightWalk.SetKind(RIGHT, RIGHT, RIGHT, RIGHT, ANIMATION_FINISH);
	s_RightWalk.SetFrame(ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_FINISH);
	s_RightWalk.m_Key = { 0.0f, 100.0f, 200.0f, 300.0f };

	::AnimationTable s_UpWalk;
	s_UpWalk.SetKind(UP, UP, UP, UP, ANIMATION_FINISH);
	s_UpWalk.SetFrame(ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_FINISH);
	s_UpWalk.m_Key = { 0.0f, 100.0f, 200.0f, 300.0f };

	::AnimationTable s_DownWalk;
	s_DownWalk.SetKind(DOWN, DOWN, DOWN, DOWN, ANIMATION_FINISH);
	s_DownWalk.SetFrame(ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_FINISH);
	s_DownWalk.m_Key = { 0.0f, 100.0f, 200.0f, 300.0f };

	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = KIND_MAX;
	FrameMax = FRAME_MAX;

	/*	左アニメーション	*/
	AnimationTableList.insert(std::make_pair("LeftWalk", s_LeftWalk));
	/*	右アニメーション	*/
	AnimationTableList.insert(std::make_pair("RightWalk", s_RightWalk));
	/*	上歩行アニメーション	*/
	AnimationTableList.insert(std::make_pair("UpWalk", s_UpWalk));
	/*	下歩行アニメーション	*/
	AnimationTableList.insert(std::make_pair("DownWalk", s_DownWalk));
}
