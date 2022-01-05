#include "Shelf.h"

Shelf::Shelf(string in_Name) : Actor(in_Name)
{
}

bool Shelf::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Shelf";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(1000.0f - 40.0f, 940.0f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 0.5f);
	col->SetOffset(0.0f, 1.02f);

	return true;
}


/****	デバッグ	****/
void Shelf::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
