#include "Umbrella.h"

Umbrella::Umbrella(string in_Name) : Actor(in_Name)
{
}

bool Umbrella::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Umbrella";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(1100.0f - 100.0f, 1280.0f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 1.0f);
	//col->SetOffset(-0.02f, -2.15f);
	col->SetOffset(0.0f, 0.0f);
	return true;
}


/****	デバッグ	****/
void Umbrella::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
