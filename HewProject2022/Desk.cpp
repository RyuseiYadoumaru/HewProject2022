#include "Desk.h"

Desk::Desk(string in_Name) : Actor(in_Name)
{
}

bool Desk::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "desk_2";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Scale.Set(1.6f, 1.6f, 1.0f);
	transform->Position.Set(-2630.0f, 320.0f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 0.3f);
	col->SetOffset(-0.02f, -2.15f);

	return true;
}


/****	デバッグ	****/
void Desk::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
