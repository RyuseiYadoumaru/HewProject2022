//*****************************************************************************
//!	@file	Engine/Create/Animation.cpp
//!	@brief	
//!	@note	アニメーションクラス
//!	@note	アニメーションの基底クラス。継承することで使用できる。
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Animation.h"
#include "../Runtime/Tools/SystemTimer.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Create::Animation::Animation()
{
	m_speed = 0.0f;
	m_animationFrame = 1;
	m_kind = 1;
	m_time = 0;
}

//==============================================================================
//!	@fn		Init
//!	@brief	初期化
//!	@param	
//!	@retva	
//==============================================================================
void Create::Animation::Init()
{
	/*	スピード設定	*/
	m_speed = 1.0f;

	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

}

//==============================================================================
//!	@fn		Play
//!	@brief	再生
//!	@param	アニメーションテーブル
//!	@retva	
//==============================================================================
void Create::Animation::Play(std::vector<int> in_AnimTable)
{
	// 種類設定 (DOWN,LEFT,RIGHT,UP)
	m_kind = in_AnimTable[0];

	// デルタタイムを取得し加算
	SystemTimer* Timer = SystemTimer::Instance();
	m_time += Timer->DeltaTime() * m_speed;

	// アニメーションテーブル取得
	int AnimationCounter = ((int)m_time % (sizeof(in_AnimTable) / sizeof(int))) + 1;

	// アニメーションループ
	if (in_AnimTable[AnimationCounter] == ANIMATION_LOOP)
	{
		AnimationCounter = 1;
		m_time = 0;
	}

	// アニメーションテーブル更新
	m_animationFrame = in_AnimTable[AnimationCounter];

}
