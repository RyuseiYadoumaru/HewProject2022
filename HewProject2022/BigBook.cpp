#include "BigBook.h"

BigBook::BigBook(string in_Name) : Actor(in_Name)
{
}

bool BigBook::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "book_b";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	float HalfSizeX = m_SpriteRenderer->GetSize().x / 2.0f;
	float PosX = ROAD_WIDTH - HalfSizeX - TILE_WIDTH / 2.0f;
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(PosX, 1080.0f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	//col->SetSize(1.0f, 0.3f);
	//col->SetOffset(-0.02f, -2.15f);

	return true;
}


/****	デバッグ	****/
void BigBook::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
