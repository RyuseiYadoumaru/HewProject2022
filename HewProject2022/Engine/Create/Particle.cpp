//*****************************************************************************
//!	@file	Engine/Create/Particle.cpp
//!	@brief	
//!	@note	パーティクルクラス
//!	@note	パーティクルの基底クラス。継承することで使用できる。
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Particle.h"
#include "../Runtime/Tools/Log.h"
#include "../Timer/GameTimer.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Create::Particle::Particle()
{
	m_ParticleName = "Name";
	m_ParticleFrame = 0;
	m_time = 0;
	m_Counter = 0;
	FrameMax = 0;
	State = PARTICLE_STOP;
}

//==============================================================================
//!	@fn		Init
//!	@brief	初期化
//!	@param	
//!	@retva	
//==============================================================================
void Create::Particle::Init()
{
	/*	表示テクスチャ初期化	*/
	m_ParticleFrame = 0;
}

//==============================================================================
//!	@fn		Play
//!	@brief	再生
//!	@param	パーティクルテーブル
//!	@retva	パーティクルステータス
//==============================================================================
int Create::Particle::Play()
{
	/****	パーティクル開始処理	***/
	if (State == PARTICLE_FINISH) return PARTICLE_FINISH;

	//アニメーションステータス
	State = PARTICLE_PLAY;
	//現在のアニメーション
	std::vector<int>& NowTable = m_Particle.m_Frame;
	std::vector<float>& NowKey = m_Particle.m_Key;

	if (NowTable.size() == 0)
	{
		Log::LogError("アニメーションの名前が間違えています");
		return PARTICLE_NAME_ERROR;
	}

	// デルタタイムを取得し加算
	m_time += GameEngine::GameTimer::deltaTime();

	// アニメーションループ
	if (NowTable[m_Counter + 1] == PARTICLE_FINISH)
	{
		State = PARTICLE_PLAY;
		m_Counter = 0;
		m_time = 0.0f;
	}

	//アニメーションカウンタ更新
	else if (m_time >= NowKey[m_Counter + 1])
	{
		//Keyタイムになったらanimationフレームを更新する
		m_Counter++;
	}

	// アニメーションテーブル更新
	m_ParticleFrame = NowTable[m_Counter];

	return State;
}

//==============================================================================
//!	@fn		PlayOneShot
//!	@brief	１回再生
//!	@param	パーティクルテーブル
//!	@retva	パーティクルステータス
//==============================================================================
int Create::Particle::PlayOneShot()
{

	/****	パーティクル開始処理	***/
	if (State == PARTICLE_FINISH) return PARTICLE_FINISH;

	//アニメーションステータス
	State = PARTICLE_PLAY;

	//現在のアニメーション
	std::vector<int>& NowTable = m_Particle.m_Frame;
	std::vector<float>& NowKey = m_Particle.m_Key;

	if (NowTable.size() == 0)
	{
		Log::LogError("アニメーションの名前が間違えています");
		return PARTICLE_NAME_ERROR;
	}

	// デルタタイムを取得し加算
	m_time += GameEngine::GameTimer::fixedDeltaTime();

	// アニメーションループ
	if (NowTable[m_Counter + 1] == PARTICLE_FINISH)
	{
		State = PARTICLE_STOP;
		m_Counter = 0;
		m_time = 0.0f;
		return State;
	}

	//アニメーションカウンタ更新
	else if (m_time >= NowKey[m_Counter + 1])
	{
		//Keyタイムになったらanimationフレームを更新する
		m_Counter++;
	}

	// アニメーションテーブル更新
	m_ParticleFrame = NowTable[m_Counter];
	return State;
}

//==============================================================================
//!	@fn		End
//!	@brief	終了処理
//!	@param	
//!	@retva	
//==============================================================================
int Create::Particle::End()
{
	m_ParticleFrame = 256;
	return PARTICLE_FINISH;
}
