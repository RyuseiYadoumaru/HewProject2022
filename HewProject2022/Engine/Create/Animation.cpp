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
//!	@fn		Play
//!	@brief	再生
//!	@param	アニメーションテーブル
//!	@retva	アニメーションステータス
//==============================================================================
int  Create::Animation::Play(std::string AnimName)
{
	/*	初期化	*/
	AnimStart(AnimName);

	//アニメーションステータス
	int State = ANIMATION_PLAY;

	//現在のアニメーション
	std::vector<int> NowTable = AnimationTableList[AnimName].m_Frame;
	std::vector<int> NowKind = AnimationTableList[AnimName].m_Kind;
	std::vector<float>& NowKey = AnimationTableList[AnimName].m_Key;

	// デルタタイムを取得し加算
	SystemTimer* Timer = SystemTimer::Instance();
	m_time += GameEngine::GameTimer::deltaTime();

	// アニメーションループ
	if (NowTable[m_AnimationCounter + 1] == ANIMATION_FINISH)
	{
		State = ANIMATION_FINISH;
		m_AnimationCounter = 0;
		m_time = 0.0f;
	}

	//アニメーションカウンタ更新
	else if (m_time >= NowKey[m_AnimationCounter + 1])
	{
		//Keyタイムになったらanimationフレームを更新する
		m_AnimationCounter++;
	}

	//アニメーション種類更新
	m_kind = NowKind[m_AnimationCounter];

	// アニメーションテーブル更新
	m_animationFrame = NowTable[m_AnimationCounter];

	return State;
}

//==============================================================================
//!	@fn		CreateAnimation
//!	@brief	アニメーション生成
//!	@param	アニメーションテーブル
//!	@retva	
//==============================================================================
void Create::Animation::CreateAnimation(std::string in_Name, ::AnimationTable in_AnimTable)
{
	in_AnimTable.m_Frame.push_back(ANIMATION_FINISH);
	AnimationTableList.insert(std::make_pair(in_Name, in_AnimTable));
}

//==============================================================================
//!	@fn		AnimStart
//!	@brief	アニメーション初期化
//!	@param	アニメーション名前
//!	@retva	
//==============================================================================

void Create::Animation::AnimStart(std::string in_AnimName)
{
	if (m_AnimationName != in_AnimName)
	{
		//アニメーションが変わった時に初期化する
		m_AnimationCounter = 0;
		m_time = 0.0f;
		m_AnimationName = in_AnimName;

	}
}
