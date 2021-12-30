#include "Table.h"

Table::Table(string in_Name) : Actor(in_Name)
{
}

bool Table::Start()
{

#if 1
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "desk";
	m_SpriteRenderer->Init();

	//奥行きなし設定
	transform->Scale.Set(3.0f, 3.0f, 1.0f);
	//transform->Position.Set(365.0f, 1225.0f + 160, 0.0f);
	transform->Position.Set(-2810.0f, 580.0f, 0.0f);
	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	//奥行きなし設定
	col->SetSize(0.97f, 0.3f);
	col->SetOffset(0.0f, -0.725f);
#else

	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "desk_2";
	m_SpriteRenderer->Init();

	//奥行きあり設定
	transform->Scale.Set(2.0f, 2.0f, 1.0f);
	transform->Position.Set(800.0f, 1170.0f, 0.0f);


	//奥行きあり設定
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(0.97f, 0.3f);
	col->SetOffset(-0.025f, -2.05f);

#endif

	return true;
}


/****	デバッグ	****/
void Table::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
