#include "SelectAnim.h"

void SelectAnim::Init()
{
	/*	セレクト移動チュートリアル	*/
	/*::AnimationTable set_SelectTutorial;
	set_SelectTutorial.SetKind(KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_2, KIND::MOVE_2, KIND::MOVE_2, ANIMATION_FINISH);
	set_SelectTutorial.SetFrame(TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_3, ANIMATION_FINISH);
	set_SelectTutorial.SetKey(0.0f, 300.0f, 600.0f, 900.0f, 1200.0f, 1500.0f);
	AnimationTableList.insert(std::make_pair("SelectTutorial", set_SelectTutorial));*/

	/*	アイドル状態	*/
	::AnimationTable set_SelectTutorial_Idle;
	set_SelectTutorial_Idle.SetKind(KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, ANIMATION_FINISH);
	set_SelectTutorial_Idle.SetFrame(TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_1, ANIMATION_FINISH);
	set_SelectTutorial_Idle.m_Key = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	AnimationTableList.insert(std::make_pair("SelectTutorial_Idle", set_SelectTutorial_Idle));

	/*	右に操作状態	*/
	::AnimationTable set_SelectTutorial_Right;
	set_SelectTutorial_Right.SetKind(KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, ANIMATION_FINISH);
	set_SelectTutorial_Right.SetFrame(TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, ANIMATION_FINISH);
	set_SelectTutorial_Right.m_Key = { 0.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f };
	AnimationTableList.insert(std::make_pair("SelectTutorial_Right", set_SelectTutorial_Right));

	/*	左に操作状態	*/
	::AnimationTable set_SelectTutorial_Left;
	set_SelectTutorial_Left.SetKind(KIND::MOVE_2, KIND::MOVE_2, KIND::MOVE_2, KIND::MOVE_2, KIND::MOVE_2, KIND::MOVE_2, ANIMATION_FINISH);
	set_SelectTutorial_Left.SetFrame(TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_1, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_2, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, ANIMATION_FINISH);
	set_SelectTutorial_Left.m_Key = { 0.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f };
	AnimationTableList.insert(std::make_pair("SelectTutorial_Left", set_SelectTutorial_Left));

	/*	右に最大	*/
	::AnimationTable set_SelectTutorial_Right_End;
	set_SelectTutorial_Right_End.SetKind(KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, KIND::MOVE_1, ANIMATION_FINISH);
	set_SelectTutorial_Right_End.SetFrame(TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, ANIMATION_FINISH);
	set_SelectTutorial_Right_End.m_Key = { 0.0f, 10.0f, 20.0f, 30.0f, 40.0f, 50.0f };
	AnimationTableList.insert(std::make_pair("SelectTutorial_Right_End", set_SelectTutorial_Right_End));

	/*	左に最大	*/
	::AnimationTable set_SelectTutorial_Left_End;
	set_SelectTutorial_Left_End.SetKind(KIND::MOVE_2, KIND::MOVE_2, KIND::MOVE_2, KIND::MOVE_2, KIND::MOVE_2, KIND::MOVE_2, ANIMATION_FINISH);
	set_SelectTutorial_Left_End.SetFrame(TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, TUTORIAL_ANIM::ANIM_3, ANIMATION_FINISH);
	set_SelectTutorial_Left_End.m_Key = { 0.0f, 10.0f, 20.0f, 30.0f, 40.0f, 50.0f };
	AnimationTableList.insert(std::make_pair("SelectTutorial_Left_End", set_SelectTutorial_Left_End));

	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = TUTORIAL_ANIM::ANIM_MAX;
}
