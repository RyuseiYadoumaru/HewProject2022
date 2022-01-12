#include "BlockEffect.h"

/****	コンストラクタ	****/
BlockEffect::BlockEffect
(GameObject* in_Owner,
	BlockEffect::Color in_Color,
	EFFECT_KIND in_Kind) : Effect()
{
	/*	オーナー設定	*/
	m_Owner = in_Owner;
	transform = m_Owner->transform;

	/*	色設定	*/
	m_MyColor = in_Color;

	/*	種類設定	*/
	m_Kind = in_Kind;

}

bool BlockEffect::Start()
{
	switch (m_MyColor)
	{
	case Color::BLUE:
		BlueStart();
		break;
	case Color::RED:
		RedStart();
		break;
	}
	/*	アニメーションコンポーネント	*/
	m_Animator = AddComponent<Animator>(m_EffectAnimation);
	m_SpriteRenderer->Init();
	return true;
}

bool BlockEffect::Update()
{
	transform = m_Owner->transform;
	//transform->Update();
	m_Animator->Update();
	m_SpriteRenderer->Update();
	return true;
}

/****	描画	****/
bool BlockEffect::Render()
{
	m_SpriteRenderer->Render();
	return true;
}

bool BlockEffect::End()
{
	m_SpriteRenderer->Release();
	delete m_EffectAnimation;
	ComponentList.clear();

	return true;
}

/****	赤初期化	****/
void BlockEffect::RedStart()
{
	switch (m_Kind)
	{
	case EFFECT_KIND::MAGIC:
		m_SpriteRenderer->SetSprite("red1-20");
		m_EffectAnimation = new  BlockMagicAnimController;
		break;

	case EFFECT_KIND::MOVE:
		m_SpriteRenderer->SetSprite("red21-35");
		m_EffectAnimation = new  BlockMoveAnimController;
		break;

	case EFFECT_KIND::RESET:
		m_SpriteRenderer->SetSprite("red35-50");
		m_EffectAnimation = new  BlockResetAnimController;
		break;

	}

}

/****	青初期化	****/
void BlockEffect::BlueStart()
{
	switch (m_Kind)
	{
	case EFFECT_KIND::MAGIC:
		m_SpriteRenderer->SetSprite("blue1-20");
		m_EffectAnimation = new  BlockMagicAnimController;
		break;

	case EFFECT_KIND::MOVE:
		m_SpriteRenderer->SetSprite("blue21-35");
		m_EffectAnimation = new  BlockMoveAnimController;
		break;

	case EFFECT_KIND::RESET:
		m_SpriteRenderer->SetSprite("blue35-50");
		m_EffectAnimation = new  BlockResetAnimController;
		break;

	}
}
