#include "Toy.h"

Toy::Toy(string in_Name) : Actor(in_Name)
{
}

bool Toy::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Toy";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Scale.Set(2.0f, 2.0f, 1.0f);
	transform->Position.Set(1000.0f, 1080.0f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 0.615f);
	col->SetOffset(0.0f, 0.625f);

	return true;
}


/****	デバッグ	****/
void Toy::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
