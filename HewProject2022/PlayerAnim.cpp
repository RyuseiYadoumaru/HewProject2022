#include "PlayerAnim.h"

void PlayerAnim::Init()
{
	// アニメーション設定	
	int set_LeftWalk[] = { LEFT, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };

	int set_RightWalk[] = { RIGHT, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };

	int set_DownWalk[] = { DOWN, ANIM_1, ANIM_2, ANIM_3, ANIM_2,ANIMATION_LOOP };

	int set_UpWalk[] = { UP, ANIM_1, ANIM_2, ANIM_3, ANIM_2, ANIMATION_LOOP };


	/*	スピード設定	*/
	m_speed = 1.0f;

	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	左アニメーション	*/
	left_walk.assign(&set_LeftWalk[0], &set_LeftWalk[sizeof(set_LeftWalk) / sizeof(int)]);

	/*	右アニメーション	*/
	right_walk.assign(&set_RightWalk[0], &set_RightWalk[sizeof(set_RightWalk) / sizeof(int)]);

	/*	下歩行アニメーション	*/
	down_walk.assign(&set_DownWalk[0], &set_DownWalk[sizeof(set_DownWalk) / sizeof(int)]);

	/*	上歩行アニメーション	*/
	up_walk.assign(&set_UpWalk[0], &set_UpWalk[sizeof(set_UpWalk) / sizeof(int)]);

}
