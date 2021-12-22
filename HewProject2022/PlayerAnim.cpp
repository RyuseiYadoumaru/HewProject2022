#include "PlayerAnim.h"

void PlayerAnim::Init()
{
	// アニメーション設定	
	std::vector<int> set_LeftWalk{ LEFT, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };

	std::vector<int> set_RightWalk{ RIGHT, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };

	std::vector<int> set_DownWalk{ DOWN, ANIM_1, ANIM_2, ANIM_3, ANIM_2,ANIMATION_LOOP };

	std::vector<int> set_UpWalk{ UP, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };


	/*	スピード設定	*/
	m_speed = 1.0f;

	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = KIND_MAX;
	FrameMax = FRAME_MAX;

	/*	左アニメーション	*/
	CreateAnimation("LeftWalk", set_LeftWalk);
	/*	右アニメーション	*/
	CreateAnimation("RightWalk", set_RightWalk);
	/*	下歩行アニメーション	*/
	CreateAnimation("DownWalk", set_DownWalk);
	/*	上歩行アニメーション	*/
	CreateAnimation("UpWalk", set_UpWalk);
}
