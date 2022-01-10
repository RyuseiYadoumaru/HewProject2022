#include "Plants.h"

Plants::Plants(string in_Name) : Actor(in_Name)
{
}

bool Plants::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Plants";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Scale.Set(2.0f, 2.0f, 1.0f);
	transform->Position.Set(1000.0f, 1040.0f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 0.1f);
	col->SetOffset(0.0f, -0.4f);

	return true;
}


/****	デバッグ	****/
void Plants::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
