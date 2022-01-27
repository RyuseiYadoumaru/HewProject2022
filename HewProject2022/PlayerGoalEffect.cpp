#include "PlayerGoalEffect.h"

PlayerGoalEffect::PlayerGoalEffect(string in_Name) : Actor(in_Name)
{
}

bool PlayerGoalEffect::Start()
{
	m_SpriteRenderer->SpriteName = "last";
	m_SpriteRenderer->Init();
	float PosX = MAPSIZE_WIDTH - 1000.0f;
	float PosY = MAPSIZE_HEIGHT / 2.0f;
	transform->Position.Set(0, 0, 0.0f);
	//GetComponent<SpriteRenderer>()->Color.a = 0;
	transform->Scale.Set(0.4f, 1.7f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_PlayerEffectController);

	return true;
}

void PlayerGoalEffect::EF_Start()
{
	//GetComponent<SpriteRenderer>()->Color.a = 1;
	m_PlayerEffectController.AnimState = PlayerEffectController::PLAYER_EFFECT;
}
