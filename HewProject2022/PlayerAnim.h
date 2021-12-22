#pragma once
#include "ydmEngine.h"

/* 方向 */
enum KIND
{
	DOWN,  // 下方向
	LEFT,  // 左方向
	RIGHT, // 右方向
	UP,    // 上方向

	KIND_MAX
};

/* パターン */
enum PA
{
	ANIM_1, // アニメーション1
	ANIM_2, // アニメーション2
	ANIM_3, // アニメーション3

	PA_MAX

};

class PlayerAnim : public Create::Animation
{
public:
	void Init() override;

	vector<int> left_walk;  // 左歩行アニメーション 
	vector<int> right_walk; // 右歩行アニメーション
	vector<int> down_walk;  // 下歩行アニメーション
	vector<int> up_walk;    // 上歩行アニメーション

};

