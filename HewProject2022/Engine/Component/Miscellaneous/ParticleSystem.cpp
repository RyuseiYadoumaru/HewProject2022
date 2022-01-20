//*****************************************************************************
//!	@file	Engine/Component/Miscellaneous/ParticleSystem.cpp
//!	@brief	
//!	@note	パーティクルシステムクラス
//!	@note	パーティクルを管理する
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "ParticleSystem.h"
#include "../../Create/Particle.h"
#include "../SpriteRenderer.h"
#include "../../Create/GameObject.h"
#include "../../Runtime/Tools/Log.h"

//==============================================================================
//!	@fn		Init
//!	@brief　初期化
//!	@param	パーティクル
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::ParticleSystem::Init(Create::Particle* in_Particle = nullptr)
{

	if (in_Particle == nullptr)
	{
		Log::LogError("パーティクルデータがありません");
		return false;
	}

	/*	パーティクル設定	*/
	m_Pariticle = in_Particle;
	m_Pariticle->Init();

	/*	テクスチャサイズ設定	*/
	float Width = 1.0f / m_Pariticle->GetFrameMax();
	float Height = 1.0f;
	Owner->GetComponent<SpriteRenderer>()->SetTexSize(Width, Height);

	m_Status = PARTICLE_STATUS::STOP;
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief　更新
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::ParticleSystem::Update()
{
	if (m_Pariticle == nullptr)
	{
		return false;
	}

	switch (m_Status)
	{
		/*	ループ再生	*/
	case GameEngine::ParticleSystem::LOOP:
		m_Pariticle->Play();
		break;

		/*	１回再生	*/
	case GameEngine::ParticleSystem::ONE_SHOT:
		if (m_Pariticle->PlayOneShot() == PARTICLE_STOP)
			m_Status = ParticleSystem::STOP;
		break;

		/*	ストップ	*/
	case GameEngine::ParticleSystem::STOP:
		m_Pariticle->StateStop();
		break;

		/*	終了	*/
	case GameEngine::ParticleSystem::END:
		m_Pariticle->StateFinish();
		m_Pariticle->End();
		break;
	}

	/*	UVタイリング更新	*/
	Owner->GetComponent<SpriteRenderer>()->UTiling = (float)m_Pariticle->GetFrame();
	Owner->GetComponent<SpriteRenderer>()->VTiling = 0.0f;

	return true;
}

//==============================================================================
//!	@fn		SetParticle
//!	@brief	パーティクルセット
//!	@param	
//!	@retval	
//==============================================================================
void GameEngine::ParticleSystem::SetParticle(PARTICLE_STATUS in_Status, Create::Particle* in_Particle)
{
	/*	パーティクル初期化	*/
	if (in_Particle != nullptr)
	{
		m_Pariticle = in_Particle;
		m_Pariticle->Init();
	}

	/*	ステータス	*/
	m_Status = in_Status;

}
