//*****************************************************************************
//!	@file	Engine/Create/Animation.cpp
//!	@brief	
//!	@note	アニメーションクラス
//!	@note	アニメーションの基底クラス。継承することで使用できる。
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Animation.h"
#include "../Runtime/Tools/SystemTimer.h"
#include "../Timer/GameTimer.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Create::Animation::Animation()
{
	m_AnimationName = "Name";
	m_animationFrame = 0;
	m_AnimationCounter = 0;
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
	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

}

//==============================================================================
//!	@fn		PlayLoop
//!	@brief	ループ再生
//!	@param	アニメーションテーブル
//!	@retva	
//==============================================================================
void Create::Animation::PlayLoop(std::string AnimName)
{
	/*	初期化	*/
	if (m_AnimationName != AnimName)
	{
		//アニメーションが変わった時に初期化する
		m_AnimationCounter = 0;
		m_time = 0.0f;
		m_AnimationName = AnimName;

	}
	//現在のアニメーション
	std::vector<int> NowTable = AnimationTableList[AnimName].m_Frame;
	std::vector<int> NowKind = AnimationTableList[AnimName].m_Kind;
	std::vector<float>& NowKey = AnimationTableList[AnimName].m_Key;

	// デルタタイムを取得し加算
	SystemTimer* Timer = SystemTimer::Instance();
	m_time += GameEngine::GameTimer::deltaTime();
	printf("DeltaTime:%f\n", GameEngine::GameTimer::deltaTime());

	// アニメーションループ
	if (NowTable[m_AnimationCounter + 1] == ANIMATION_FINISH)
	{
		printf("ループアニメーション\n");
		m_AnimationCounter = 0;
		m_time = 0;
	}

	//アニメーションカウンタ更新
	if (m_time >= NowKey[m_AnimationCounter + 1])
	{
		//Keyタイムになったらanimationフレームを更新する
		m_AnimationCounter++;
	}

	//アニメーション種類更新
	m_kind = NowKind[m_AnimationCounter];

	// アニメーションテーブル更新
	m_animationFrame = NowTable[m_AnimationCounter];
}

//==============================================================================
//!	@fn		PlayOneShot
//!	@brief	１回再生
//!	@param	アニメーションテーブル
//!	@retva	
//==============================================================================
int Create::Animation::PlayOneShot(std::string AnimName)
{
	//現在のアニメーション
	std::vector<int>& NowTable = AnimationTableList[AnimName].m_Frame;
	std::vector<int>& NowKind = AnimationTableList[AnimName].m_Kind;

	// デルタタイムを取得し加算
	SystemTimer* Timer = SystemTimer::Instance();

	// アニメーションテーブル取得
	int AnimationCounter = ((int)m_time % (sizeof(NowTable) / sizeof(int))) + 1;

	// アニメーションループ
	if (NowTable[AnimationCounter] == ANIMATION_FINISH)
	{
		AnimationCounter = 0;
		m_time = 0;
	}

	//アニメーション種類更新
	m_kind = NowKind[AnimationCounter];

	// アニメーションテーブル更新
	m_animationFrame = NowTable[AnimationCounter];

	//アニメーションが終了したら再生終了を返す
	return ANIMATION_FINISH;
}

//==============================================================================
//!	@fn		CreateAnimation
//!	@brief	アニメーション生成
//!	@param	アニメーションテーブル
//!	@retva	
//==============================================================================
void Create::Animation::CreateAnimation(std::string in_Name, ::AnimationTable in_AnimTable)
{
	AnimationTableList.insert(std::make_pair(in_Name, in_AnimTable));
}
