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
enum FRAME
{
	ANIM_1, // アニメーション1
	ANIM_2, // アニメーション2
	ANIM_3, // アニメーション3

	FRAME_MAX

};

class PlayerAnim : public Create::Animation
{
public:
	void Init() override;

};

