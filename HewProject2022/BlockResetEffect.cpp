#include "BlockResetEffect.h"
#include "BlockParticleManager.h"


/****	コンストラクタ	****/
BlockResetEffect::BlockResetEffect(NAME in_Name) : Effect(in_Name)
{
	/*	オーナー設定	*/
	m_Owner = nullptr;
	/*	色設定	*/
	EffectColor = BlockEffectColor::RED;
}

/****	初期化	****/
bool BlockResetEffect::Start()
{
	/*	エフェクト色設定	*/
	EffectColor = BlockEffectColor::RED;

	/*	トランスフォーム設定	*/
	SetOwnerPosition();
	SetSize(TILE_WIDTH, TILE_HEIGHT);
	transform->Scale.Set(2.5f, 2.5f, 0.0f);
	/*	スプライト初期化	*/
	if (EffectColor == BlockEffectColor::RED)
	{
		m_SpriteRenderer->SpriteName = "red35-50";
	}
	else if (EffectColor == BlockEffectColor::BLUE)
	{
		m_SpriteRenderer->SpriteName = "blue35-50";
	}
	m_SpriteRenderer->Init();

	/*	パーティクルシステムコンポーネント	*/
	m_ParticleSystem = AddComponent<ParticleSystem>(&m_Particle);
	m_ParticleSystem->SetParticle(ParticleSystem::ONE_SHOT);

	return true;
}

/****	更新	****/
bool BlockResetEffect::Update()
{

	//ストップ状態になったら終了する
	if (m_Particle.GetState() == PARTICLE_STOP) m_Particle.StateFinish();

	/*	終了したら破棄する　	*/
	if (m_Particle.GetState() == PARTICLE_FINISH)
	{
		BlockParticleManager::DeleteResetEffect(m_Owner->GetId().x);
		Destroy();
	}

	/*	トランスフォーム更新	*/
	SetOwnerPosition();
	return true;
}
