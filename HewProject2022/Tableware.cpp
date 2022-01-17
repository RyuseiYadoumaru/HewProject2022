#include "Tableware.h"

Tableware::Tableware(string in_Name) : Actor(in_Name)
{
}

bool Tableware::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Tableware";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(1000.0f, 940.0f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 0.95f);
	col->SetOffset(0.0f, 1.01f);

	return true;
}


/****	デバッグ	****/
void Tableware::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
