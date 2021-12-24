#include "Table.h"

Table::Table(string in_Name) : Actor(in_Name)
{
}

bool Table::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Table";
	m_SpriteRenderer->Init();
	m_SpriteRenderer->Color.Set(0.8f, 0.6f, 0.3f, 1.0f);

	transform->Scale.Set(10.0f, 4.0f, 4.0f);
	transform->Position.Set(350.0f, 1000.0f, 0.0f);


	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(0.97f, 0.3f);
	col->SetOffset(0.0f, -0.5f);

	return true;
}


/****	デバッグ	****/
void Table::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
