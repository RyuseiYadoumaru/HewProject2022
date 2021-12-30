#include "Chair.h"

Chair::Chair(string in_Name) : Actor(in_Name)
{
}

bool Chair::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Chair_2";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Scale.Set(3.33f, 3.33f, 1.0f);
	transform->Position.Set(-2630.0f, 320.0f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 0.3f);
	col->SetOffset(-0.02f, -2.15f);

	return true;
}


/****	デバッグ	****/
void Chair::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
