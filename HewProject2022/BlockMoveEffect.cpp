#include "BlockMoveEffect.h"
#include "BlockParticleManager.h"

/****	コンストラクタ	****/
BlockMoveEffect::BlockMoveEffect(NAME in_Name) : Effect(in_Name)
{
	/*	オーナー設定	*/
	m_Owner = nullptr;
	/*	色設定	*/
	EffectColor = BlockEffectColor::RED;
}

/****	初期化	****/
bool BlockMoveEffect::Start()
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
		m_SpriteRenderer->SpriteName = "red35";
	}
	else if (EffectColor == BlockEffectColor::BLUE)
	{
		m_SpriteRenderer->SpriteName = "blue35";
	}
	m_SpriteRenderer->Init();

	/*	パーティクルシステムコンポーネント	*/
	m_ParticleSystem = AddComponent<ParticleSystem>(&m_Particle);
	m_ParticleSystem->SetParticle(ParticleSystem::LOOP);

	return true;
}

/****	更新	****/
bool BlockMoveEffect::Update()
{

	/*	終了したら破棄する　	*/
	if (m_Particle.GetState() == PARTICLE_FINISH)
	{
		Destroy();
		BlockParticleManager::DeleteMoveEffect(m_Owner->GetId().x);
	}

	/*	トランスフォーム更新	*/
	SetOwnerPosition();
	return true;
}
