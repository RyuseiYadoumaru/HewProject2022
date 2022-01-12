#include "BlockMagicEffect.h"


/****	コンストラクタ	****/
BlockMagicEffect::BlockMagicEffect(NAME in_Name) : Effect(in_Name)
{
	/*	オーナー設定	*/
	m_Owner = nullptr;
	/*	色設定	*/
	EffectColor = BlockEffectColor::RED;
}

/****	初期化	****/
bool BlockMagicEffect::Start()
{
	/*	エフェクト色設定	*/
	EffectColor = BlockEffectColor::RED;

	/*	トランスフォーム設定	*/
	SetOwnerTransform();
	SetSize(TILE_WIDTH, TILE_HEIGHT);

	/*	スプライト初期化	*/
	if (EffectColor == BlockEffectColor::RED)
	{
		m_SpriteRenderer->SpriteName = "red1-20";
	}
	else if (EffectColor == BlockEffectColor::BLUE)
	{
		m_SpriteRenderer->SpriteName = "blue1-20";
	}
	m_SpriteRenderer->Init();

	/*	パーティクルシステムコンポーネント	*/
	m_ParticleSystem = AddComponent<ParticleSystem>(&m_Particle);

	return true;
}

/****	更新	****/
bool BlockMagicEffect::Update()
{
	/*	エフェクト	*/
	if (Input::GetKeyTrigger(PK_1) == true)
	{
		m_ParticleSystem->SetParticle(ParticleSystem::LOOP);
	}
	if (Input::GetKeyTrigger(PK_2) == true)
	{
		m_ParticleSystem->SetParticle(ParticleSystem::ONE_SHOT);
	}
	if (Input::GetKeyTrigger(PK_3) == true)
	{
		m_ParticleSystem->SetParticle(ParticleSystem::END);
	}

	/*	トランスフォーム更新	*/
	SetOwnerTransform();
	return true;
}
